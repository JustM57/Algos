#include <iostream>

using namespace std;


class Queue {
private:
    long capacity;
    const long INITIAL_CAPACITY = 1024;
    long *a;
    long start;
    long end;
    long ssize;

    void increase_capacity() {
        long* b = new long[capacity * 2];
        for (long i = 0; i < ssize; ++i) {
            b[i] = a[(i + start) % capacity];
        }
        delete [] a;
        a = b;
        start = 0;
        end = ssize;
        capacity *= 2;
    }

    void decrease_capacity() {
        long* b = new long[capacity / 2];
        for (long i = 0; i < ssize; ++i) {
            b[i] = a[(i + start) % capacity];
        }
        delete [] a;
        a = b;
        start = 0;
        end = ssize;
        capacity /= 2;
    }

public:
    Queue() {
        start = 0;
        end = 0;
        ssize = 0;
        capacity = INITIAL_CAPACITY;
        a = new long[capacity];
    }

    ~Queue() { delete [] a; }

    void push(long x) {
        a[end % capacity] = x;
        ++end;
        end %= capacity;
        ++ssize;
        if (ssize == capacity) increase_capacity();
    }

    long front() { return a[start]; }

    void pop() {
        ++start;
        start %= capacity;
        --ssize;
        if ((capacity > INITIAL_CAPACITY) && (ssize <= (capacity / 4))) {
            decrease_capacity();
        }
    }

    long size() { 
        return ssize; }
};


int main() {
    int m;
    cin >> m;
    Queue que = Queue();
    string op;
    long a;
    for (int i = 0; i < m; ++i) {
        cin >> op;
        if (op == "+") {
            cin >> a;
            que.push(a);
        } else {
            cout << que.front() << '\n';
            que.pop();
        }
    }
    return 0;
}