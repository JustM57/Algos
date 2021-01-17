#include <iostream>
#include <string>
#include <ctime>


using namespace std;
const int MIN_INT = -2147483648;
const int32_t MOD = 1000000000;


struct Node {
    int32_t key;
    Node* left;
    Node* right;
    uint64_t sum;
    int height;

    Node(int32_t x) {
        this->key = x;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
        this->sum = x;
    };

    int get_height(Node* a) {
        if (a == nullptr) {
            return 0;
        }
        return a->height;
    };

    uint64_t get_sum(Node* a) {
        if (a == nullptr) {
            return 0;
        }
        return a->sum;
    };

    void fix_sum() {
        this->sum = get_sum(this->left) + get_sum(this->right) + this->key;
    };

    int balance() {
        return get_height(this->right) - get_height(this->left);
    };

    void fix_height() {
        this->height = max(get_height(this->left), get_height(this->right)) + 1;
        this->fix_sum();
    };
};


int get_height(Node* a) {
    if (a == nullptr) {
        return 0;
    }
    return a->height;
};


uint64_t get_sum(Node* a) {
    if (a == nullptr) {
        return 0;
    }
    return a->sum;
};


class AVLTree {
private:
    Node* root;
    int size;

    Node* search(Node* local_root, int32_t x) {
        if (local_root == nullptr) {
            return nullptr;
        }
        if (local_root->key == x) {
            return local_root;
        } else {
            if (x < local_root->key) {
                return search(local_root->left, x);
            } else {
                return search(local_root->right, x);
            }
        }
    };

    Node* balance(Node* p) {
        p->fix_height();
        if (p->balance() == 2) {
            //правое дерево слишком длинное
            Node* q = p->right;
            if (get_height(q->left) > get_height(q->right)) {
                p = bigRotateLeft(p);
            } else {
                p = smallRotateLeft(p);
            }
        }
        if (p->balance() == -2) {
            //левое дерево слишком длинное
            Node* q = p->left;
            if (get_height(q->right) > get_height(q->left)) {
                p = bigRotateRight(p);
            } else {
                p = smallRotateRight(p);
            }
        }
        return p;
    };

    Node* insert(Node* local_root, int32_t x) {
        if (local_root == nullptr) {
            ++this->size;
            return new Node(x);
        } else {
            if (x < local_root->key) {
                local_root->left = insert(local_root->left, x);
            }
            if (x > local_root->key) {
                local_root->right = insert(local_root->right, x);
            }
            return balance(local_root);
        }
    };

    void printTree(Node* local_root) {
        if (local_root!=nullptr) {
            printTree(local_root->left);
            cout << local_root->key << ' ' << local_root->height << ' ' << local_root->sum << '\n';
            printTree(local_root->right);
        }
    };

    Node* smallRotateRight(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        p->fix_height();
        q->fix_height();
        return q;
    };

    Node* smallRotateLeft(Node* p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        p->fix_height();
        q->fix_height();
        return q;
    };

    Node* bigRotateRight(Node* p) {
        p->left = smallRotateLeft(p->left);
        p = smallRotateRight(p);
        return p;
    };

    Node* bigRotateLeft(Node* p) {
        p->right = smallRotateRight(p->right);
        p = smallRotateLeft(p);
        return p;
    };

public:
    AVLTree(): root(nullptr), size(0) {};

    void print() {
        printTree(this->root);
    }

    void insert(int32_t x) {
        if (!this->exists(x)) {
            this->root = insert(this->root, x);
        }
    };

    bool exists(int32_t x) {
        return (search(this->root, x) != nullptr);
    };

    int get_size() {
        return this->size;
    }

    uint64_t sum(int32_t x, int32_t y) {
        //Node - теперь в каждой вершине будем хранить cумму дерева.
        //соотвественно при балансировке также будем фиксить сумму
        Node* l = this->root;
        uint64_t cur = l->sum;
        while ((l != nullptr) && (l->key != x)) {
            if (l->key > x) {
                l = l->left;
            } else {
                cur -= get_sum(l->left) + l->key;
                l = l->right;
            }
        }
        if ((l != nullptr) && (l->key == x)) {
            cur -= get_sum(l->left);
        }
        Node* r = this->root;
        while ((r != nullptr) && (r->key != y)) {
            if (r->key > y) {
                cur -= get_sum(r->right) + r->key;
                r = r->left;
            } else {
                r = r->right;
            }
        }
        if ((r != nullptr) && (r->key == y)) {
            cur -= get_sum(r->right);
        }
        return cur;
    };
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string command;
    int32_t x, y, n;
    AVLTree tree = AVLTree(); 
    cin >> n;
    uint64_t res = 0;
    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "+") {
            cin >> x;
            tree.insert((int)((res + x) % MOD));
            res = 0;
        }
        if (command == "?") {
            cin >> x >> y;
            if ((tree.get_size() != 0 ) && (y >= x)) {
                res = tree.sum(x, y);
            } else {
                res = 0;
            }
            cout << res << '\n';
        }
        if (command == "p") {
            tree.print();
        }
    }
    // srand((uint32_t)time(NULL));
    // for (int i = 0; i < 300000; ++i) {
    //     x = rand() % 2;
    //     if ((x % 2) == 1) {
    //         x = rand() % MOD;
    //         x = (res + x) % MOD;
    //         tree.insert(x);
    //     } else {
    //         x = rand() % MOD;
    //         y = rand() % MOD;
    //         if (y < x) swap(x, y);
    //         if ((tree.get_size() != 0 ) && (y >= x)) {
    //             res = tree.sum(x, y);
    //         } else {
    //             res = 0;
    //         }
    //         cout << res << '\n';
    //     }
    // }
    return 0;
}
