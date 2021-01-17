#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <utility>

using namespace std;
const int INITIAL_CAPACITY = 1000;
const int SIMPLE_SIZE = 26;
const int MAX_P_MULT = 100;
const int SIMPLE[SIMPLE_SIZE] = {
    31, 29 ,1597, 2897, 5741, 7561, 28657, 33461, 43261, 
    96557, 426389, 514229, 4713, 5795, 6611, 18496, 32292, 32469,
    59656, 90825, 262419, 361275, 481899, 1354828, 6328548, 6679881
};
const int MAX_A = 1000;


struct Node {
    string key;
    string value;
    Node* next = nullptr;
    Node* prev = nullptr;
    Node* prev_x = nullptr;
    Node* next_x = nullptr;

    Node() : key(""), value(""), next(nullptr), prev(nullptr), next_x(nullptr), prev_x(nullptr){}
};

struct List {
    Node* first;
    Node* last;
    int size;

    List() {
        first = new Node();
        last = first;
        size = 1;
    }

    ~List() {
        while (first != last){
            Node* next = first->next;
            delete first;
            first = next;
        }
        delete first;
    }

    pair<bool, Node*> put(string key, string value, Node* prev) {
        Node* tmp = this->first;
        bool res = false;
        while ((tmp != last) && (tmp->key != key)) {
            tmp = tmp->next;
        }
        if (tmp == this->last) {
            Node* new_last = new Node();
            tmp->next = new_last;
            new_last->prev = tmp;
            this->last = tmp->next;
            res = true;
            ++size;
            tmp->prev_x = prev;
            if ((prev != nullptr)) prev->next_x = tmp;  //&& (prev != tmp)
            prev = tmp;
        }
        tmp->key = key;
        tmp->value = value;
        pair<bool, Node*> res_pair = {res, prev};
        return res_pair;
    }

    void get(string key) {
        Node* tmp = first;
        while ((tmp != last) && (tmp->key != key)) {
            tmp = tmp->next;
        }
        if (tmp->key == key) {
            cout << tmp->value << '\n';
        } else cout << "none" << '\n';
    }

    void get_prev(string key) {
        Node* tmp = first;
        while ((tmp != last) && (tmp->key != key)) {
            tmp = tmp->next;
        }
        if (tmp->key == key) {
            if (tmp->prev_x != nullptr) {
                cout << tmp->prev_x->value << '\n';
            } else cout << "none" << '\n';
        } else cout << "none" << '\n';
    }

    void get_next(string key) {
        Node* tmp = first;
        while ((tmp != last) && (tmp->key != key)) {
            tmp = tmp->next;
        }
        if (tmp->key == key) {
            if (tmp->next_x != nullptr) {
                cout << tmp->next_x->value << '\n';
            } else cout << "none" << '\n';
        } else cout << "none" << '\n';
    }


    pair<bool, Node*> erase(string key, Node* prev) {
        Node* tmp = first;
        while ((tmp != last) && (tmp->key != key)) {
            tmp = tmp->next;
        }
        bool was_deleted = false;
        if (tmp->key == key) {
            if (tmp->prev_x != nullptr) {
                tmp->prev_x->next_x = tmp->next_x;
            }
            if (tmp->next_x != nullptr) {
                tmp->next_x->prev_x = tmp->prev_x;
            } else prev = tmp->prev_x;
            if (tmp == first) {
                Node* new_first = first->next;
                delete first;
                first = new_first;
                first->prev = nullptr;
            } else {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                delete tmp;
            }
            was_deleted = true;
        }
        pair<bool, Node*> res = {was_deleted, prev};
        return res;
    }
};

class Map {
private:
    List* a;
    int size;
    int capacity;
    function<int(string)> hash;
    Node* prev;

    function<int(string)> generate_hash(int m) {
        srand(time(NULL));
        int a = rand() % MAX_A;
        int p = 1;
        while ((p < m) || (p > m * MAX_P_MULT)) {
            p = SIMPLE[rand() % SIMPLE_SIZE];
        }
        function<int(string)> hash = [a, p, m](string x) { 
            int res = 0;
            for (int i = 0; i < x.length(); ++i) {
                res = (res * a + (int)x[i]) % p;
            }
            res = res % m;
            if (res < 0) res += m;
            return res;
        };
        return hash;
    }

    void increase_capacity() {
        int new_capacity = max(INITIAL_CAPACITY, (this->size * 2));
        List* new_a = new List[new_capacity];
        Node* new_prev = nullptr;
        function<int(string)> new_hash = generate_hash(new_capacity);
        Node* iter = prev;
        while (iter->prev_x != nullptr) iter = iter->prev_x;
        while (iter != nullptr) {
            int key = new_hash(iter->key);
            pair<bool, Node*> res = new_a[key].put(iter->key, iter->value, new_prev);
            new_prev = res.second;
            iter = iter->next_x;
        }
        delete [] this->a;
        this->capacity = new_capacity;
        this->a = new_a;
        this->hash = new_hash;
        this->prev = new_prev;
    }

public:
    Map() {
        this->size = 0;
        this->capacity = INITIAL_CAPACITY;
        this->a = new List[this->capacity];
        this->hash = generate_hash(this->capacity);
        this->prev = nullptr;
    }

    Map(int c) {
        this->size = 0;
        this->capacity = c;
        this->a = new List[this->capacity];
        this->hash = generate_hash(this->capacity);
        this->prev = nullptr;
    }

    ~Map(){
        delete [] a;
    }

    void put(pair<string, string> x) {
        int key = hash(x.first);
        pair<bool, Node*> res = a[key].put(x.first, x.second, prev);
        prev = res.second;
        if (res.first) {
            ++this->size;
            if ((this->size) > this->capacity ) increase_capacity();
        }
    }
    
    void delete_(string x) {
        int key = hash(x);
        pair<bool, Node*> res= a[key].erase(x, prev);
        prev = res.second;
        if (res.first) --this->size;   
    }

    void get(string x) {
        int key = hash(x);
        a[key].get(x);
    }

    void prev_(string x) {
        int key = hash(x);
        a[key].get_prev(x);
    }

    void next(string x) {
        int key = hash(x);
        a[key].get_next(x);
    }

    int getSize() const {
        return size;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string word, key, value;
    Map map = Map();
    pair<string, string> elms;
    while (cin >> word) {
        cin >> key;
        if (word == "put") {
            cin >> value;
            elms = {key, value};
            map.put(elms);
        }
        if (word == "get") map.get(key);
        if (word == "delete") map.delete_(key);
        if (word == "prev") map.prev_(key);
        if (word == "next") map.next(key);
    }
    return 0;
}