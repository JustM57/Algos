#include <iostream>

using namespace std;


struct ListNode{
    ListNode(long x) : elem(x), min_list(x), prev(nullptr) {}
    ListNode(long x, long min_list, ListNode* prev) : elem(x), min_list(min_list), prev(prev) {}
    long elem;
    long min_list;
    ListNode* prev;
};

class MinStack {
private:
    ListNode* head;
    ListNode* tail;
    int size;
public:
    MinStack() : head(nullptr), tail(nullptr), size(0) {};
    void push(long x) {
        if (size == 0) {
            tail = new ListNode(x);
            head = tail;
        } else {
            long min_x = min(x, tail -> min_list);
            tail = new ListNode(x, min_x, tail);
        }
        ++size;
    };
    void pop() {
        ListNode* prev = (*tail).prev;
        delete tail;
        tail = prev;
        --size;
    };
    long min_elem() {
        return tail -> min_list;
    };
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    cin >> n;
    int op;
    long num;
    MinStack stack = MinStack();
    for (int i = 0; i < n; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> num;
            stack.push(num);
        } else {
            if (op == 2) stack.pop(); else {
                cout << stack.min_elem() << '\n';
            }
        } 
    }
    return 0;
}