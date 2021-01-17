#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;
const int INITIAL_CAPACITY = 50000;


class Set {
private:
    int* a;
    int size;
    int capacity;
    int rip_size;
    function<int(int)> hash;

    function<int(int)> generate_hash(int m) {
        srand(time(NULL));
        int a = rand() % 1000;
        int simple[26] = {31, 29 ,1597, 2897, 5741, 7561, 28657, 33461, 43261, 
        96557, 426389, 514229, 4713, 5795, 6611, 18496, 32292, 32469,
        59656, 90825, 262419, 361275, 481899, 1354828, 6328548, 6679881};
        int p = 1;
        while ((p < m) || (p > m*100)) {
            p = simple[rand() % 26];
        }
        function<int(int)> hash = [a, p, m](int x) { 
            int res = ((a * x) % p) % m;
            if (res < 0) res += m;
            return res;
        };
        return hash;
    }

    void increase_capacity() {
        int new_capacity = max(INITIAL_CAPACITY, (this->size * 4));
        int* new_a = new int[new_capacity];
        for (int i = 0; i < new_capacity; ++i) new_a[i] = NULL_VALUE;
        function<int(int)> new_hash = generate_hash(new_capacity);
        for (int i = 0; i < this->capacity; ++i) {
            if ((this->a[i] != NULL_VALUE) && (this->a[i] != RIP_VALUE)) {
                int key = new_hash(this->a[i]);
                while (new_a[key] != NULL_VALUE) {
                    key = (key + 1) % new_capacity;
                }
                new_a[key] = this->a[i];
            }
        }
        delete [] this->a;
        this->rip_size = 0;
        this->capacity = new_capacity;
        this->a = new_a;
        this->hash = new_hash;
    }

public:
    Set() {
        this->size = 0;
        this->rip_size = 0;
        this->capacity = INITIAL_CAPACITY;
        this->a = new int[this->capacity];
        for (int i = 0; i < this->capacity; ++i) this->a[i] = NULL_VALUE;
        this->hash = generate_hash(this->capacity);
    }

    Set(int c) {
        this->size = 0;
        this->rip_size = 0;
        this->capacity = c;
        this->a = new int[this->capacity];
        for (int i = 0; i < this->capacity; ++i) this->a[i] = NULL_VALUE;
        this->hash = generate_hash(this->capacity);
    }

    ~Set(){
        delete [] a;
    }

    void insert(int x) {
        int key = hash(x);
        while ((this->a[key] != NULL_VALUE) && (this->a[key] != x)) {
            key = (key + 1) % this->capacity;
        }
        if (this->a[key] == NULL_VALUE) {
            this->a[key] = x;
            ++this->size;
            if ((this->size + this->rip_size) >= this->capacity / 2) {
                increase_capacity();
                // cout << this->capacity;
            }
        }
    }
    
    void delete_(int x) {
        int key = hash(x);
        while ((this->a[key] != NULL_VALUE) && (this->a[key] != x)) {
            key = (key + 1) % this->capacity;
        }
        if (this->a[key] == x) {
            this->a[key] = RIP_VALUE;
            --this->size;
            ++this->rip_size;
        }      
    }

    void exists(int x) {
        int key = hash(x);
        while ((this->a[key] != NULL_VALUE) && (this->a[key] != x)) {
            key = (key + 1) % this->capacity;
        }
        if (this->a[key] == x) cout << "true\n"; else cout << "false\n";
    }

    int getSize() const {
        return size;
    }
};


struct Node {
    string key;
    Set values;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node() : key(""), values(Set()), next(nullptr), prev(nullptr) {}
};

struct List {
    Node* first;
    Node* last;

    List() {
        first = new Node();
        last = first;
    }

    ~List() {
        delete first;
    }

    bool put(string key, string value) {
        Node* tmp = this->first;
        bool res = false;
        while (tmp != last){
            if ((tmp->key == key) && (tmp->value == value)) return res;
            tmp = tmp->next;
        }
        if (tmp == this->last) {
            Node* new_last = new Node();
            tmp->next = new_last;
            new_last->prev = tmp;
            this->last = tmp->next;
            res = true;
            tmp->key = key;
            tmp->value = value;
            return res;
        }
    }

    void get(string key) {
        Node* tmp = first;
        vector<string> counter;
        while (tmp != last) {
            if (tmp->key == key) counter.push_back(tmp->value);
            tmp = tmp->next;
        }
        cout << counter.size();
        for (int i = 0; i < counter.size(); ++i) cout << ' ' << counter[i];
        cout << '\n';
    }

    bool erase(string key, string value) {
        Node* tmp = first;
        bool res = false;
        while (tmp != last) {
            if ((tmp->key == key) && (tmp->value == value)) {
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
                res = true;
                return res;
            }
            tmp = tmp->next;
        }
        return res;
    }

    void erase_all(string key) {
        Node* tmp = first;
        while (tmp != last) {
            if (tmp->key == key) {
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
            }
            tmp = tmp->next;
        }
    }
};

class Map {
private:
    List* a;
    int size;
    int capacity;
    function<int(string)> hash;

    function<int(string)> generate_hash(int m) {
        srand(time(NULL));
        int a = rand() % 1000;
        int simple[26] = {31, 29 ,1597, 2897, 5741, 7561, 28657, 33461, 43261, 
        96557, 426389, 514229, 4713, 5795, 6611, 18496, 32292, 32469,
        59656, 90825, 262419, 361275, 481899, 1354828, 6328548, 6679881};
        int p = 1;
        while ((p < m) || (p > m*100)) {
            p = simple[rand() % 26];
        }
        function<int(string)> hash = [a, p, m](string x) { 
            int res = 0;
            for (int i = 0; i < x.length(); ++i) res = (res * a + (int)x[i]) % p;
            res = res % m;
            if (res < 0) res += m;
            return res;
        };
        return hash;
    }

public:
    Map() {
        this->size = 0;
        this->capacity = INITIAL_CAPACITY;
        this->a = new List[this->capacity];
        this->hash = generate_hash(this->capacity);
    }

    ~Map(){
        delete [] a;
    }

    void put(pair<string, string> x) {
        int key = hash(x.first);
        bool res = a[key].put(x.first, x.second);
    }
    
    void delete_(pair<string, string> x) {
        int key = hash(x.first);;
        bool res = a[key].erase(x.first, x.second);   
    }

    void delete_all(string x) {
        int key = hash(x);
        a[key].erase_all(x);   
    }

    void get(string x) {
        int key = hash(x);
        a[key].get(x);
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
        if (word == "delete") {
            cin >> value;
            elms = {key, value};
            map.delete_(elms);
        }
        if (word == "get") map.get(key);
        if (word == "deleteall") map.delete_all(key);
    }
    return 0;
}