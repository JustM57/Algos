#include <iostream>
#include <sstream>
#include <string>

using namespace std;


class Stack {
private:
    long capacity;
    const long INITIAL_CAPACITY = 1024;
    long *a;
    long ssize;

    void increase_capacity() {
        long* b = new long[capacity * 2];
        for (long i = 0; i < ssize; ++i) b[i] = a[i];
        delete [] a;
        a = b;
        capacity *= 2;
    }

    void decrease_capacity() {
        long* b = new long[capacity / 2];
        for (long i = 0; i < ssize; ++i) b[i] = a[i];
        delete [] a;
        a = b;
        capacity /= 2;
    }
public:
    Stack() {
        ssize = 0;
        capacity = INITIAL_CAPACITY;
        a = new long[capacity];
    }

    ~Stack() { delete [] a; }

    void push(long x) {
        if (ssize == capacity) increase_capacity();
        a[ssize] = x;
        ++ssize;
    }

    long back() { return a[ssize - 1]; }

    void pop() {
        --ssize;
        if ((capacity > INITIAL_CAPACITY) && (ssize <= (capacity / 4))) {
            decrease_capacity();
        }
    }

    long size() { return ssize; }
};


bool is_number(const string& s)
{
    return isdigit(s[0]);
}


long compute(char c, long a, long b)
{
    switch (c) {  
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: throw runtime_error("No such operator");
    }
}


int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    string word;
    Stack stack = Stack();
    long a;
    long b;
    long res;
    while (ss >> word) {
        if (is_number(word)) {
            stack.push(stol(word));
        } else {
            b = stack.back();
            stack.pop();
            a = stack.back();
            stack.pop();
            res = compute(word[0], a, b);
            stack.push(res);
        }
    }
    cout << stack.back();
    return 0;
}