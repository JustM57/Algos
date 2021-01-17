#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>

using namespace std;
const int NULL_VALUE = -1000000001;
const int RIP_VALUE = 1000000001;
const int INITIAL_CAPACITY = 1000;
const int SIMPLE_SIZE = 26;
const int MAX_P_MULT = 100;
const int SIMPLE[SIMPLE_SIZE] = {
    31, 29 ,1597, 2897, 5741, 7561, 28657, 33461, 43261, 
    96557, 426389, 514229, 4713, 5795, 6611, 18496, 32292, 32469,
    59656, 90825, 262419, 361275, 481899, 1354828, 6328548, 6679881
};
const int MAX_A = 1000;



class Set {
private:
    int* a;
    int size;
    int capacity;
    int rip_size;
    function<int(int)> hash;

    function<int(int)> generate_hash(int m) {
        srand(time(NULL));
        int a = rand() % MAX_A;
        int p = 1;
        while ((p < m) || (p > m * MAX_P_MULT)) {
            p = SIMPLE[rand() % SIMPLE_SIZE];
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
        for (int i = 0; i < this->capacity; ++i) {
            this->a[i] = NULL_VALUE;
        }
        this->hash = generate_hash(this->capacity);
    }

    Set(int c) {
        this->size = 0;
        this->rip_size = 0;
        this->capacity = c;
        this->a = new int[this->capacity];
        for (int i = 0; i < this->capacity; ++i) {
            this->a[i] = NULL_VALUE;
        }
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
        if (this->a[key] == x) {
            cout << "true\n";
        } else cout << "false\n";
    }

    int getSize() const {
        return size;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string word;
    int num;
    Set set = Set();
    while (cin >> word) {
        cin >> num;
        if (word == "insert") set.insert(num);
        if (word == "delete") set.delete_(num);
        if (word == "exists") set.exists(num);
    }
    return 0;
}
