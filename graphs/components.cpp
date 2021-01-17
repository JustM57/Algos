#include <iostream>
#include <map>
#include <vector>
#include <utility>


using namespace std;
const int DEFAULT_COLOR = 0;


class Graph {
private:
    map<int, vector<int>> edges;
    int size;

    void dfs(int v, vector<int>* color, int cur) {
        (*color)[v] = cur;
        vector<int> vertex = this->edges[v];
        for (const auto& u: vertex) {
            if ((*color)[u] == DEFAULT_COLOR) {
                dfs(u, color, cur);
            }
        }
    };

public:
    Graph(int n) : size(n) {};

    void add(int x, int y) {
        this->edges[x].push_back(y);
        this->edges[y].push_back(x);
    };

    pair<int, vector<int>> count_components() {
        int cnt = 0;
        vector<int> color(this->size);
        for (int v = 0; v < size; ++v) {
            if (color[v] == DEFAULT_COLOR) {
                ++cnt;
                dfs(v, &color, cnt);
            }
        }
        return {cnt, color};
    };
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int b, e;
    Graph g = Graph(n);
    for (int i = 0; i < m; ++i) {
        cin >> b >> e;
        --b;
        --e;
        g.add(b, e);
    } 
    auto res = g.count_components();
    cout << res.first << '\n';
    for (int i = 0; i < n; ++i) {
        cout << res.second[i] << ' ';
    }
    return 0;
}