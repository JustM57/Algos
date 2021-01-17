#include <iostream>
#include <map>
#include <vector>
#include <utility>


using namespace std;
const int MAX_CAPACITY = 20;


struct Edge {
    int a, b, c, f, d;
    Edge(int a, int b, int c, int f, int d) : a(a), b(b), c(c), f(f), d(d) {};
};


class Graph {
private:
    vector<Edge>* edges;
    int size;

    int pushFlow(int v, int t, int curFlow, vector<int>* used) {
        (*used)[v] = 1;
        if (v == t) {
            return curFlow;
        }
        for (auto edge = this->edges[v].begin(); edge < this->edges[v].end(); ++edge) {
            if (((*used)[edge->b] == 0) && (edge->f < edge->c)) {
                int nextFlow = min(curFlow, edge->c - edge->f);
                int delta = this->pushFlow(edge->b, t, nextFlow, used);
                if (delta > 0) {
                    edge->f += delta;
                    this->edges[edge->b][edge->d].f -= delta;
                    return delta;
                }
            }
        }
        return 0;
    };

public:
    Graph(int n) : size(n) {
        this->edges = new vector<Edge>[n];
    };

    void add(int a, int b, int c) {
        bool used = false;
        for (auto edge = this->edges[a].begin(); edge < this->edges[a].end(); ++edge) {
            if (edge->b == b) {
                used = true;
                edge->c += c;
                this->edges[edge->b][edge->d].c += c; 
                break;
            }
        }
        if (not used) {
            this->edges[a].push_back(Edge(a, b, c, 0, this->edges[b].size()));
            this->edges[b].push_back(Edge(b, a, c, 0, this->edges[a].size() - 1));
        }
    };

    int get_max_flow() {
        int ans = 0;
        int delta;
        vector<int> used;
        int s = 0;
        int t = this->size - 1;
        while (true) {
            used.assign(this->size, 0);
            delta = this->pushFlow(s, t, MAX_CAPACITY, &used);
            if (delta > 0) {
                ans += delta;
            } else {
                break;
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
    int a, c, b;
    Graph g = Graph(n);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        --a;
        --b;
        g.add(a, b, c);
    } 
    int res = g.get_max_flow();
    cout << res << '\n';
    return 0;
}