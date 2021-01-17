#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <utility>

using namespace std;
const uint32_t INITIAL_CAPACITY = 1000;
const uint32_t NULL_VALUE = -1000000001;
const uint32_t RIP_VALUE = 1000000001;
const uint32_t SET_INITIAL_CAPACITY = 1000;
const uint32_t SIMPLE_SIZE = 26;
const uint32_t MAX_P_MULT = 100;
const uint32_t SIMPLE[SIMPLE_SIZE] = {
    31, 29 ,1597, 2897, 5741, 7561, 28657, 33461, 43261, 
    96557, 426389, 514229, 4713, 5795, 6611, 18496, 32292, 32469,
    59656, 90825, 262419, 361275, 481899, 1354828, 6328548, 6679881
};
const uint32_t MAX_A = 1000;


struct Node {
    string key;
    string value;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node() : key(" "), value(" "), next(nullptr), prev(nullptr) {}
};

struct List {
    Node* first;
    Node* last;
    uint32_t size;

    List() {
        first = new Node();
        last = first;
        size = 1;
    }

    ~List() {
        delete first;
    }

    bool put(string key, string value) {
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
        }
        tmp->key = key;
        tmp->value = value;
        return res;
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


    void erase(string key) {
        Node* tmp = first;
        while ((tmp != last) && (tmp->key != key)) {
            tmp = tmp->next;
        }
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
    }
};

class Map {
private:
    List* a;
    uint32_t size;
    uint32_t capacity;
    function<uint32_t(string)> hash;

    function<uint32_t(string)> generate_hash(uint32_t m) {
        srand(time(NULL));
        uint32_t a = rand() % MAX_A;
        uint32_t p = 1;
        while ((p < m) || (p > m * MAX_P_MULT)) {
            p = SIMPLE[rand() % SIMPLE_SIZE];
        }
        function<uint32_t(string)> hash = [a, p, m](string x) { 
            uint32_t res = 0;
            for (uint32_t i = 0; i < x.length(); ++i) {
                res = (res * a + (uint32_t)x[i]) % p;
            }
            res = res % m;
            if (res < 0) res += m;
            return res;
        };
        return hash;
    }

    void increase_capacity() {
        uint32_t new_capacity = max(INITIAL_CAPACITY, (this->size * 2));
        List* new_a = new List[new_capacity];
        function<uint32_t(string)> new_hash = generate_hash(new_capacity);
        for (uint32_t i = 0; i < this->capacity; ++i) {
            Node* tmp = a[i].first;
            while (tmp != a[i].last) {
                uint32_t key = new_hash(tmp->key);
                new_a[key].put(tmp->key, tmp->value);
                tmp = tmp->next;
            }
        }
        delete [] this->a;
        this->capacity = new_capacity;
        this->a = new_a;
        this->hash = new_hash;
    }

public:
    Map() {
        this->size = 0;
        this->capacity = INITIAL_CAPACITY;
        this->a = new List[this->capacity];
        this->hash = generate_hash(this->capacity);
    }

    Map(uint32_t c) {
        this->size = 0;
        this->capacity = c;
        this->a = new List[this->capacity];
        this->hash = generate_hash(this->capacity);
    }

    ~Map(){
        delete [] a;
    }

    void put(pair<string, string> x) {
        uint32_t key = hash(x.first);
        bool was_new = a[key].put(x.first, x.second);
        if (was_new) {
            ++this->size;
            if ((this->size) > this->capacity ) increase_capacity();
        }
    }
    
    void delete_(string x) {
        uint32_t key = hash(x);;
        a[key].erase(x);
        --this->size;   
    }

    void get(string x) {
        uint32_t key = hash(x);
        a[key].get(x);
    }

    uint32_t getSize() const {
        return size;
    }
};


uint32_t main() {
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
    }
    return 0;
}