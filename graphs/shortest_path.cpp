#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <climits>


using namespace std;


struct Edge {
    int from;
    int to;
    int weight;
    Edge(int x, int y, int w) : from(x), to(y), weight(w) {};
};


class Graph {
private:
    int V;
    int E;
    vector<Edge>* edges;

public:
    Graph(int n, int m) : V(n), E(m) {
        this->edges = new vector<Edge>[n + 1];
    }; 

    ~Graph() {
        delete [] this->edges;
    };

    void add_edge(int x, int y, int w) {
        this->edges[x].push_back(Edge(x, y, w));
        this->edges[y].push_back(Edge(y, x, w));
    };

    void shortes_distance() {
        int* used = new int[this->V + 1];
        int* depth = new int[this->V + 1];
        for (int i = 0; i <= this->V; ++i) {
            used[i] = 0;
            depth[i] = INT_MAX;
        }
        used[1] = 1;
        depth[1] = 0;
        set<pair<int, int>> priority_queue;
        priority_queue.insert({0, 1});
        for (int i = 1; i <= this->V; ++i) {
            if (priority_queue.size() == 0) {
                break;
            }
            int next = priority_queue.begin()->second;
            priority_queue.erase(*priority_queue.begin());
            used[next] = 1;
            for (auto edge = this->edges[next].begin(); edge != this->edges[next].end(); ++edge) {
                if (used[edge->to] == 0) {
                    priority_queue.erase({depth[edge->to], edge->to});
                    depth[edge->to] = min(depth[edge->to], depth[next] + edge->weight);
                    priority_queue.insert({depth[edge->to], edge->to});
                }
            }
        }
        for (int i = 1; i <= this->V; ++i) {
            cout << depth[i] << ' ';
        }
        delete [] used;
        delete [] depth;
    };
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Graph g = Graph(n, m);
    int x, y, w;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        g.add_edge(x, y, w);
    }
    g.shortes_distance();
    return 0;
}