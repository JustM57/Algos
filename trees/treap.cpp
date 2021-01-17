#include <iostream>
#include <string>
#include <utility>
#include <ctime>

using namespace std;
const int MIN_INT = -2147483648;
const int MAX_VAL = 2147483647;


struct Node {
    int key;
    int value;
    Node* left;
    Node* right;

    Node(int x, int y) {
        this->key = x;
        this->value = y;
        this->left = nullptr;
        this->right = nullptr;
    };
};

class Treap {
private:
    Node* root;

    pair<Node*, Node*> split(Node* local_root, int key) {
        if (local_root == nullptr) {
            return {nullptr, nullptr};
        }
        pair<Node*, Node*> new_trees;
        if (local_root->key > key) {
            new_trees = split(local_root->left, key);
            local_root->left = new_trees.second;
            return {new_trees.first, local_root};
        } else {
            new_trees = split(local_root->right, key);
            local_root->right = new_trees.first;
            return {local_root, new_trees.second};
        }
    }

    Node* merge(Node* t1, Node* t2) {
        if (t1 == nullptr) {
            return t2;
        }
        if (t2 == nullptr) {
            return t1;
        }
        if (t1->value > t2->value) {
            t1->right = merge(t1->right, t2);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            return t2;
        }
    }

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

    void printTree(Node* local_root) {
        if (local_root != nullptr) {
            printTree(local_root->left);
            cout << local_root->key << ' ' << local_root->value <<'\n';
            printTree(local_root->right);
        }
    };

    Node* insert(Node* t, int x, int y) {
        if ((t != nullptr) && (t->value >= y)) {
            if (x < t->key) {
                t->left = insert(t->left, x, y);
            } else {
                t->right = insert(t->right, x, y);
            }
        } else {
            pair<Node*, Node*> trees = split(t, x);        
            Node* new_node = new Node(x, y); 
            new_node->left = trees.first;
            new_node->right = trees.second;
            t = new_node;
        }
        return t;
    }

    Node* remove(Node* t, int x) {
        if (t == nullptr) {
            return nullptr;
        }
        if (x < t->key) {
            t->left = remove(t->left, x);
        }
        if (x > t->key) {
            t->right = remove(t->right, x);
        } 
        if (x == t->key) {
            Node* new_t = merge(t->left, t->right);
            delete t;
            t = new_t;
        }
        return t;
    }

public:
    Treap(): root(nullptr) {};

    void print() {
        printTree(this->root);
    }

    void insert(int x) {
        int y = rand() % MAX_VAL;
        if (search(this->root, x) == nullptr) {
            this->root = insert(this->root, x, y);
        }   
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

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(0));
    string word;
    int x;
    Treap tree = Treap(); 
    while (cin >> word) {
        cin >> x;
        if (word == "insert") {
            tree.insert(x);
        }
        if (word == "exists") {
            if (tree.exists(x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
        if (word == "next") {
            x = tree.next(x);
            if (x == MIN_INT) {
                cout << "none\n";
            } else {
                cout << x << '\n';
            }
        }
        if (word == "prev") {
            x = tree.prev(x);
            if (x == MIN_INT) {
                cout << "none\n";
            } else {
                cout << x << '\n';
            }
        }
        if (word == "delete") {
            tree.remove(x);
        }
        if (word == "print") {
            tree.print();
        }
    }
    // int u = 1000;
    // int v = u / 2;
    // for (int i = 0; i < 100000; ++i) {
    //     int x = rand() % 5;
    //     if (x == 0) {
    //         tree.insert(-v + rand() % u);
    //     }
    //     if (x == 1) {
    //         tree.remove(-v + rand() % u);
    //     }
    //     if (x == 2) {
    //         x = -v + rand () % u;
    //         if (tree.exists(x)) {
    //             cout << "true\n";
    //         } else {
    //             cout << "false\n";
    //         }
    //     }
    //     if (x == 3) {
    //         x = -v + rand () % u;
    //         x = tree.next(x);
    //         if (x == MIN_INT) {
    //             cout << "none\n";
    //         } else {
    //             cout << x << '\n';
    //         }
    //     }
    //     if (x == 4) {
    //         x = -v + rand() % u;
    //         x = tree.prev(x);
    //         if (x == MIN_INT) {
    //             cout << "none\n";
    //         } else {
    //             cout << x << '\n';
    //         }
    //     }
    // }
    return 0;
}
