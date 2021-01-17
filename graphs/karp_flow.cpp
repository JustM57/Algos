#include <iostream>
#include <map>
#include <vector>
#include <utility>


using namespace std;
const int MAX_CAPACITY = 10000;


struct Edge {
    int a, b, c, f, d, i;
    Edge() {};
    Edge(int a, int b, int c, int f, int d, int i) : a(a), b(b), c(c), f(f), d(d), i(i) {};
};


class Graph {
private:
    vector<Edge>* edges;
    int size;
    int m;
    vector<pair<int, int>> pipes;

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
    Graph(int n, int m) : size(n) , m(m) {
        this->edges = new vector<Edge>[n];
        this->pipes = vector<pair<int, int>>(m);
    };

    ~Graph(){
        delete [] this->edges;
    };

    void add(int idx, int a, int b, int c) {
        this->edges[a].push_back(Edge(a, b, c, 0, this->edges[b].size(), idx));
        int d = this->edges[a].size() - 1;
        this->pipes[idx] = {a, d};
        this->edges[b].push_back(Edge(b, a, c, 0, d, idx));
    };

    void get_max_flow() {
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
        cout << ans << '\n';
        for (auto pipe = this->pipes.begin(); pipe < this->pipes.end(); ++pipe) {
            cout << this->edges[pipe->first][pipe->second].f << '\n';
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int a, c, b;
    Graph g = Graph(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        --a;
        --b;
        g.add(i, a, b, c);
    } 
    g.get_max_flow();
    return 0;
}