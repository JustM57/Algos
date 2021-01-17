#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <stack>


using namespace std;
const pair<int, int> JUMPS[8] = {
    {1, 2,}, {2, 1},
    {-1, -2,}, {-2, -1},
    {1, -2,}, {-2, 1},
    {-1, 2,}, {2, -1}
};


class Graph {
private:
    int n;

    vector<pair<int, int>> get_edges(pair<int, int>v) {
        vector<pair<int, int>> edges;
        for (int idx = 0; idx < 8; ++idx) {
            int i = JUMPS[idx].first;
            int j = JUMPS[idx].second;
            if ((v.first + i < n) && (v.first + i > -1)) {
                if ((v.second + j < n) && (v.second + j > -1)) {
                    edges.push_back({v.first + i, v.second + j});
                }
            }
        }
        return edges;
    }

public:
    Graph(int n) : n(n) {}; 

    void bfs(pair<int, int> first, pair<int, int> last) {
        pair<int, int> v = first;
        int** used = new int*[this->n];
        // int** depth = new int*[this->n];
        pair<int, int>** p = new pair<int, int>*[this->n];
        for (int i = 0; i < n; ++i) {
            used[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                used[i][j] = 0;
            }
            // depth[i] = new int[n];
            p[i] = new pair<int, int>[n];
        }
        queue<pair<int, int>> q;
        q.push(v);
        // depth[v.first][v.second] = 1;
        while (used[last.first][last.second] == 0) {
            v = q.front();
            q.pop();
            vector<pair<int, int>> edges = this->get_edges(v);
            for (auto u = edges.begin(); u != edges.end(); ++u) {
                if (used[u->first][u->second] == 0) {
                    used[u->first][u->second] = 1;
                    q.push(*u);
                    // depth[u->first][u->second] = depth[v.first][v.second] + 1;
                    p[u->first][u->second] = v;
                }
            }
        }

        v = last;
        stack<pair<int, int>> jumps;
        while (v != first) {
            jumps.push(v);
            v = p[v.first][v.second];
        }
        jumps.push(v);
        cout << jumps.size() << '\n';
        while (jumps.size() > 0) {
            v = jumps.top();
            jumps.pop();
            cout << v.first + 1 << ' ' << v.second + 1 << '\n';
        }

        for (int i = 0; i < n; ++i) {
            delete [] used[i];
            // delete [] depth[i];
            delete [] p[i];
        }
        delete [] used;
        // delete [] depth;
        delete [] p;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int x1, x2, y1, y2;
    Graph g = Graph(n);
    cin >> x1 >> y1 >> x2 >> y2;
    --x1; 
    --x2; 
    --y1; 
    --y2;
    g.bfs({x1, y1}, {x2, y2});
    return 0;
}