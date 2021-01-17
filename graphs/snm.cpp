#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

struct Node {
    int anc, rang, max_el, min_el, size;
    Node() {};
    Node(int x) : anc(x), rang(0), max_el(x), min_el(x), size(1) {};
};


class SNM {
private:
    Node* a;
    int get_(int x) {
        if (this->a[x].anc != x) {
            this->a[x].anc = get_(this->a[x].anc);
        }
        return this->a[x].anc;
    };

public:
    SNM(int n) {
        this->a = new Node[n+1];
        for (int i = 0; i <= n; ++i) {
            a[i] = Node(i);
        }
    };

    ~SNM() {
        delete [] this->a;
    };

    void get(int x) {
        x = get_(x);
        cout << this->a[x].min_el << ' ' << this->a[x].max_el << ' ' << this->a[x].size << '\n';
    }

    void union_(int x, int y) {
        x = get_(x);
        y = get_(y);
        if (x == y) {
            return;
        }
        if (this->a[x].rang > this->a[y].rang) {
            swap(x, y);
        }
        if (this->a[x].rang == this->a[y].rang) {
            ++this->a[y].rang;
        }
        this->a[x].anc = y;
        this->a[y].min_el = min(this->a[y].min_el, this->a[x].min_el);
        this->a[y].max_el = max(this->a[y].max_el, this->a[x].max_el);
        this->a[y].size = this->a[y].size + this->a[x].size;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int x, y;
    string s;
    SNM g = SNM(n);
    while (cin >> s) {
        if (s == "union") {
            cin >> x >> y;
            g.union_(x, y);
        }
        if (s == "get") {
            cin >> x;
            g.get(x);
        }
    }
    return 0;
}