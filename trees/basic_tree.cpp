#include <iostream>
#include <string>


using namespace std;
const int MIN_INT = -2147483648;


struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int x) {
        this->key = x;
        this->left = nullptr;
        this->right = nullptr;
    };
};


class BasicTree {
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
            return local_root;
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
        return local_root;
    };

    void printTree(Node* local_root) {
        if (local_root!=nullptr) {
            printTree(local_root->left);
            cout << local_root->key << ' ';
            printTree(local_root->right);
        }
    };

public:
    BasicTree(): root(nullptr), size(0) {};

    void print() {
        printTree(this->root);
    }

    void insert(int x) {
        Node* assigned = insert(this->root, x);
        if (size == 1) {
            this->root = assigned;
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
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    string word;
    int x;
    BasicTree tree = BasicTree(); 
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
    }
    return 0;
}
