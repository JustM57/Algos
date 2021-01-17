#include <iostream>
#include <string>
#include <utility>
#include <ctime>

using namespace std;
const int MIN_INT = -2147483648;
const int MAX_VAL = 2147483647;


struct Node {
    int size;
    int value;
    int prior;
    Node* left;
    Node* right;

    Node(int x, int y) {
        this->size = 1;
        this->value = x;
        this->prior = y;
        this->left = nullptr;
        this->right = nullptr;
    };

    int get_size(Node* a) {
        if (a == nullptr) {
            return 0;
        }
        return a->size;
    };

    void fix() {
        this->size = get_size(this->left) + get_size(this->right) + 1;
    }
};


int get_size(Node* a) {
    if (a == nullptr) {
        return 0;
    }
    return a->size;
};


class SecretTreap {
private:
    Node* root;

    pair<Node*, Node*> split(Node* local_root, int key) {
        if (local_root == nullptr) {
            return {nullptr, nullptr};
        }
        pair<Node*, Node*> new_trees;
        if (get_size(local_root->left) > key) {
            new_trees = split(local_root->left, key);
            local_root->left = new_trees.second;
            local_root->fix();
            return {new_trees.first, local_root};
        } else {
            new_trees = split(local_root->right, key - get_size(local_root->left) - 1);
            local_root->right = new_trees.first;
            local_root->fix();
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
        if (t1->prior > t2->prior) {
            t1->right = merge(t1->right, t2);
            t1->fix();
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            t2->fix();
            return t2;
        }
    }

    Node* insert(Node* t, int i, int x, int y) {
        if ((t != nullptr) && (t->prior >= y)) {
            int key = get_size(t->left);
            if (i < key) {
                t->left = insert(t->left, i, x, y);
            } else {
                t->right = insert(t->right, i - key - 1, x, y);
            }
        } else {
            pair<Node*, Node*> trees = split(t, i);        
            Node* new_node = new Node(x, y); 
            new_node->left = trees.first;
            new_node->right = trees.second;
            t = new_node;
        }
        t ->fix();
        return t;
    }

    Node* remove(Node* t, int i) {
        if (t == nullptr) {
            return nullptr;
        }
        int key = get_size(t->left);
        if (i < key) {
            t->left = remove(t->left, i);
        }
        if (i > key) {
            t->right = remove(t->right, i - key - 1);
        } 
        if (i == key) {
            Node* new_t = merge(t->left, t->right);
            delete t;
            t = new_t;
        }
        if (t != nullptr) {
            t ->fix();
        }
        return t;
    }

    void printTree(Node* local_root) {
        if (local_root != nullptr) {
            printTree(local_root->left);
            cout << local_root->value << ' ';
            printTree(local_root->right);
        }
    };

public:
    SecretTreap(): root(nullptr) {};

    void insert(int i, int x) {
        int y = rand() % MAX_VAL;
        this->root = insert(this->root, i, x, y);
    };

    void remove(int i) {
        this->root = remove(this->root, i);
    };

    void print() {
        cout << get_size(this->root) << '\n';
        printTree(this->root);
        cout << '\n';
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(0));
    string word;
    int n, m, i;
    int x;
    SecretTreap tree = SecretTreap(); 
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        tree.insert(i, x);
    }
    for (int j = 0; j < m; ++j) {
        cin >> word;
        cin >> i;
        --i;
        if (word == "add") {
            cin >> x;
            tree.insert(i, x);
        }
        if (word == "del") {
            // --i;
            tree.remove(i);
        }
    }
    tree.print();
    return 0;
}