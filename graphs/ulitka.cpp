#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <queue>
 
 
using namespace std;
const int MAX_CAPACITY = 2;
 
 
struct Edge {
    int a, b, c, f, d, i;
    Edge* anc;
    Edge() {};
    Edge(int a, int b, int c, int f, int d, int i) : a(a), b(b), c(c), f(f), d(d), i(i) {};
};
 
 
class Graph {
private:
    vector<Edge>* edges;
    int size;
    int m;
    int U;
    vector<pair<int, int>> pipes;
 
    int pushFlow(int s, int t, int curFlow, vector<int>* used, int delta) {
        queue<pair<int, Edge*>> priority_queue;
        int v = s;
        Edge* prev = nullptr;
        (*used)[v] = 1;
        priority_queue.push({v, prev});
        while (priority_queue.size() != 0){
            int v = priority_queue.front().first;
            prev = priority_queue.front().second;
            if (v == t) {
                while (prev != nullptr) {
                    prev->f += curFlow;
                    this->edges[prev->b][prev->d].f -= curFlow;
                    prev = prev->anc;   
                }
                return curFlow;
            } 
            priority_queue.pop();
            for (auto edge = this->edges[v].begin(); edge < this->edges[v].end(); ++edge) {
                if (((*used)[edge->b] == 0) && (edge->f + delta <= edge->c)) {
                    edge->anc = prev;
                    curFlow = min(curFlow, edge->c - edge->f);
                    priority_queue.push({edge->b, &(*edge)});
                    (*used)[edge->b] = 1;
                }
            }
        }
        return 0;
    };
 
    void search(int s, int t, int curFlow, vector<int>* used, int delta, vector<int>** path, int i) {
        queue<pair<int, Edge*>> priority_queue;
        int v = s;
        Edge* prev = nullptr;
        (*used)[v] = 1;
        priority_queue.push({v, prev});
        while (priority_queue.size() != 0){
            int v = priority_queue.front().first;
            prev = priority_queue.front().second;
            if (v == t) {
                (*path)[i].push_back(t);
                prev->f = 0;
                while (prev != nullptr) {
                    (*path)[i].push_back(prev->a);
                    prev = prev->anc;   
                }
                return;
            } 
            priority_queue.pop();
            for (auto edge = this->edges[v].begin(); edge < this->edges[v].end(); ++edge) {
                if (((*used)[edge->b] == 0)  && (edge->f == 1)) {
                    edge->anc = prev;
                    priority_queue.push({edge->b, &(*edge)});
                    (*used)[edge->b] = 1;
                }
            }
        }
    };
 
public:
    Graph(int n, int m) : size(n) , m(m), U(0) {
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
        this->edges[b].push_back(Edge(b, a, 0, 0, d, idx));
        this->U = max(this->U, c);
    };
 
    void get_max_flow(int s, int t) {
        int ans = 0;
        int delta;
        vector<int> used;
        int i = 0;
        vector<int>* path = new vector<int>[2];
        while (ans < 2) {
            used.assign(this->size, 0);
            delta = this->pushFlow(s, t, MAX_CAPACITY, &used, 1);
            if (delta > 0) {
                ans += delta;
                ++i;
            } else {
                break;
            }
        }
        used.assign(this->size, 0);
        this->search(s, t, MAX_CAPACITY, &used, 1, &path, 0);
        used.assign(this->size, 0);
        this->search(s, t, MAX_CAPACITY, &used, 1, &path, 1);
        if (ans == 2) {
            cout << "YES" << '\n';
            for (int i = 0; i < 2; ++i) {
                for (auto v = path[i].rbegin(); v < path[i].rend(); ++v) {
                    cout << (*v) + 1 << ' ';
                } 
                cout << '\n';
            }
        } else {
            cout << "NO";
        }
        delete [] path;
    }
};
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, s, t;
    cin >> n >> m;
    cin >> s >> t;
    --s;
    --t;
    int a, c, b;
    Graph g = Graph(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        --a;
        --b;
        g.add(i, a, b, 1);
    } 
    g.get_max_flow(s, t);
    return 0;
}