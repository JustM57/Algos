#include <iostream>
#include <string>
#include <algorithm>
#include <utility>


using namespace std;

struct Node {
    int anc, rang, exp;
    Node() {};
    Node(int x) : anc(x), rang(0), exp(0) {};
};


class SNM {
private:
    Node* a;
    int n;
    //fix get
    pair<int, int> get_(int x) {
        if (this->a[x].anc != x) {
            auto info = get_(this->a[x].anc);
            this->a[x].anc = info.first;
            this->a[x].exp += info.second;
            return {this->a[x].anc, this->a[x].exp};
        }
        return {this->a[x].anc, 0};
    };

public:
    SNM(int n) : n(n) {
        this->a = new Node[n+1];
        for (int i = 0; i <= n; ++i) {
            a[i] = Node(i);
        }
    };

    ~SNM() {
        delete [] this->a;
    };

    void get(int x) {
        auto res = get_(x);
        cout << res.second + this->a[res.first].exp << '\n';
    }

    void union_(int x, int y) {
        x = get_(x).first;
        y = get_(y).first;
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
        this->a[x].exp -= this->a[y].exp;
    }

    void add(int x, int y) {
        x = get_(x).first;
        this->a[x].exp += y;
    }

    void print(){
        for (int i = 1; i <= n; ++i) {
            cout << i << ' ' << this->a[i].exp << ' ' << this->a[i].anc << '\n';
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int x, y;
    string s;
    SNM g = SNM(n);
    for (int i = 0; i < m; ++i) {
        cin >> s;
        if (s == "join") {
            cin >> x >> y;
            g.union_(x, y);
        }
        if (s == "get") {
            cin >> x;
            g.get(x);
        }
        if (s == "add") {
            cin >> x >> y;
            g.add(x, y);
        }
        if (s == "print") {
            g.print();
        }
    }
    return 0;
}