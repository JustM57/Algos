#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <stack>
#include <set>


using namespace std;
const int DEFAULT_COLOR = 0;


class Graph {
private:
    map<int, vector<int>> edges;
    int size;
    stack<int> top_verteces;

    bool dfs(int v, vector<int>* color, stack<int>* ans) {
        (*color)[v] = 1;
        vector<int> vertex = this->edges[v];
        for (const auto& u: vertex) {
            if ((*color)[u] == DEFAULT_COLOR) {
                dfs(u, color, ans);
            }
            // if ((*color)[u] == 1) {
            //     return true;
            // }
        }
        (*color)[v] = 2;
        (*ans).push(v);
        return false;
    };

    void dfs_comp(int v, vector<int>* color, int cur) {
        (*color)[v] = cur;
        vector<int> vertex = this->edges[v];
        for (const auto& u: vertex) {
            if ((*color)[u] == DEFAULT_COLOR) {
                dfs_comp(u, color, cur);
            }
        }
    };

public:
    Graph(int n) : size(n) {};

    void add(int x, int y) {
        this->edges[x].push_back(y);
    };

    stack<int> top_sort() {
        vector<int> color(this->size);
        stack<int> ans;
        bool error = false;
        for (int v = 0; v < size; ++v) {
            if (color[v] == DEFAULT_COLOR) {
                error = dfs(v, &color, &ans);
                // if (error) {
                //     ans = stack<int>();
                //     ans.push(-2);
                //     return ans;
                // }
            }
        }
        return ans;
    };

    void get_verteces(stack<int> x) {
        this->top_verteces = x;
    }

    pair<int, vector<int>> count_components() {
        int cnt = 0;
        vector<int> color(this->size);
        int n = this->top_verteces.size();
        for (int i = 0; i < n; ++i) {
            int v = this->top_verteces.top();
            this->top_verteces.pop();
            if (color[v] == DEFAULT_COLOR) {
                ++cnt;
                dfs_comp(v, &color, cnt);
            }
        }
        return {cnt, color};
    };

    int condensation_edges() {
        set<pair<int, int>> new_edges;
        auto components = this->count_components();
        for (const auto& v: edges) {
            for (const auto& u: v.second) {
                if (components.second[v.first] != components.second[u]) {
                    new_edges.insert({components.second[v.first], components.second[u]});
                }
            }
        }
        return new_edges.size();
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int b, e;
    Graph g = Graph(n);
    Graph g_reverced = Graph(n);
    for (int i = 0; i < m; ++i) {
        cin >> b >> e;
        --b;
        --e;
        g.add(b, e);
        g_reverced.add(e, b);
    }
    stack<int> res = g_reverced.top_sort();
    g.get_verteces(res);
    cout << g.condensation_edges() << '\n';
    return 0;
}