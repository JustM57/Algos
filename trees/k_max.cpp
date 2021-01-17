#include <iostream>
#include <string>


using namespace std;
const int MIN_INT = -2147483648;


struct Node {
    int key;
    Node* left;
    Node* right;
    int size;
    int height;

    Node(int x) {
        this->key = x;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
        this->size = 1;
    };

    int get_height(Node* a) {
        if (a == nullptr) {
            return 0;
        }
        return a->height;
    };

    int get_size(Node* a) {
        if (a == nullptr) {
            return 0;
        }
        return a->size;
    };

    void fix_size() {
        this->size = get_size(this->left) + get_size(this->right) + 1;
    };

    int balance() {
        return get_height(this->right) - get_height(this->left);
    };

    void fix_height() {
        this->height = max(get_height(this->left), get_height(this->right)) + 1;
        this->fix_size();
    };
};


int get_height(Node* a) {
    if (a == nullptr) {
        return 0;
    }
    return a->height;
};


int get_size(Node* a) {
    if (a == nullptr) {
        return 0;
    }
    return a->size;
};

class AVLTree {
private:
    Node* root;
    int size;

    Node* search(Node* local_root, int x) {
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

    Node* insert(Node* local_root, int x) {
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

    Node* findMax(Node* v) {
        while (v->right != nullptr) {
            v = v->right;
        }
        return v;
    };

    Node* remove(Node* local_root, int x) {
        Node* tmp;
        if (local_root == nullptr) {
            return nullptr;
        }
        if (x < local_root->key) {
            local_root->left = remove(local_root->left, x); 
        }      
        if (x > local_root->key) {
            local_root->right = remove(local_root->right, x);
        }
        if (x == local_root->key) {
            if ((local_root->right == nullptr) & (local_root->left == nullptr)) {
                --this->size;
                delete local_root;               
                local_root = nullptr;
            } else {
                if (local_root->left == nullptr) {
                    tmp = local_root->right;
                    --this->size;
                    delete local_root;
                    local_root = tmp;
                } else {
                    if (local_root->right == nullptr) {
                        tmp = local_root->left;
                        --this->size;
                        delete local_root;
                        local_root = tmp;
                    } else {
                        local_root->key = findMax(local_root->left)->key;
                        local_root->left = remove(local_root->left, local_root->key);
                    }
                }
            }
        }
        if (local_root != nullptr) {
            return balance(local_root);
        } else {
            return local_root;
        }
    };

    void printTree(Node* local_root) {
        if (local_root!=nullptr) {
            printTree(local_root->left);
            cout << local_root->key << ' ' << local_root->height << ' ' << local_root->size << '\n';
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

    void insert(int x) {
        this->root = insert(this->root, x);
    };

    void remove(int x) {
        this->root = remove(this->root, x);
    };

    bool (exists)(int x) {
        return (search(this->root, x) != nullptr);
    };

    int next(int x) {
        int res = MIN_INT;
        Node* v = this->root;
        while (v != nullptr) {
            if (v->key > x) {
                res = v->key;
                v = v->left;
            } else {
                v = v->right;
            }
        }
        return res;
    };

    int prev(int x) {
        int res = MIN_INT;
        Node* v = this->root;
        while (v != nullptr) {
            if (v->key >= x) {
                v = v->left;
            } else {
                res = v->key;
                v = v->right;
            }
        }
        return res;
    };

    int max_k(int x) {
        //Node - теперь в каждой вершине будем хранить размер дерева.
        //соотвественно при балансироваке также будем фиксить размер
        Node* v = this->root;
        int cur = get_size(v->right) + 1;
        while (cur != x) {
            if (cur < x) { //go left
                v = v->left;
                cur += get_size(v->right) + 1;
            } else {
                v = v->right;
                cur -= get_size(v->left) + 1;
            }
        }
        return v->key;
    };

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int command;
    int x, n;
    AVLTree tree = AVLTree(); 
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> command >> x;
        if (command == 1) {
            tree.insert(x);
        }
        if (command == -1) {
            tree.remove(x);
        }
        if (command == 0) {
            cout << tree.max_k(x) << '\n';
        }
        if (command == 2) {
            tree.print();
        }
    }
    return 0;
}
