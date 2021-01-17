#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <stack>


using namespace std;
const int DEFAULT_COLOR = 0;


class Graph {
private:
    map<int, vector<int>> edges;
    int size;

    bool dfs(int v, vector<int>* color, stack<int>* ans) {
        (*color)[v] = 1;
        vector<int> vertex = this->edges[v];
        for (const auto& u: vertex) {
            if ((*color)[u] == DEFAULT_COLOR) {
                dfs(u, color, ans);
            }
            if ((*color)[u] == 1) {
                return true;
            }
        }
        (*color)[v] = 2;
        (*ans).push(v);
        return false;
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
                if (error) {
                    ans = stack<int>();
                    ans.push(-2);
                    return ans;
                }
            }
        }
        return ans;
    };

    bool no_cycles() {
        
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
    stack<int> res = g.top_sort();
    n = res.size();
    for (int i = 0; i < n; ++i) {
        cout << res.top() + 1 << ' ';
        res.pop();
    }
    return 0;
}