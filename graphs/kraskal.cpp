#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <map>


using namespace std;


struct Node {
    int anc, rang, max_el, min_el, size;
    Node() {};
    Node(int x) : anc(x), rang(0){};
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

    int get(int x) {
        x = get_(x);
        return x;
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


class Graph {
private:
    int n;
    map<int, list<pair<int, int>>> edges;
public:
    Graph(int n) : n(n) {};

    void add_edge(int x, int y, int w) {
        this->edges[w].push_back({x, y});
    }

    long long min_tree_len() {
        long long ans = 0;
        SNM snm = SNM(n);
        for (auto iter_key = this->edges.begin(); iter_key != this->edges.end(); ++iter_key){
            int key = iter_key->first;
            auto val = iter_key->second;
            for (auto iter = val.begin(); iter != val.end(); ++iter) {
                if (snm.get(iter->first) != snm.get(iter->second)) {
                    ans += key;
                    snm.union_(iter->first, iter->second);
                }
            }
        }
        return ans;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int x, y, w;
    Graph g = Graph(n);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        g.add_edge(x, y, w);
        g.add_edge(y, x, w);
    }
    cout << g.min_tree_len() << '\n';
    return 0;
}