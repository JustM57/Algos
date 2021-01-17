#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <climits>


using namespace std;
const int SKIP_NODE = 100000;


struct Graph {
    int** w;
    int n;
    Graph(int n) : n(n) {
        this->w = new int*[n];
        for (int i = 0; i < n; ++i) {
            this->w[i] = new int[n];
        }
    }

    ~Graph() {
        for (int i = 0; i < this->n; ++i) {
            delete [] this->w[i];
        }
        delete [] this->w;
    }

    pair<bool, vector<int>> find_cycle() {
        int** d = new int*[this->n];
        for (int u = 0; u < this->n; ++u) {
            d[u] = new int[this->n];
            for (int v = 0; v < this->n; ++v) {
                d[u][v] = this->w[u][v];
            }
        }
        int** next = new int*[this->n];
        for (int u = 0; u < this->n; ++u) {
            next[u] = new int[this->n];
            for (int v = 0; v < this->n; ++v) {
                next[u][v] = v;
            }
        }
        for (int k = 0; k < this->n; ++k) {
            for (int u = 0; u < this->n; ++u) {
                for (int v = 0; v < this->n; ++v) {
                    if ((d[u][v] > d[u][k] + d[k][v]) && ((d[u][k] != SKIP_NODE) && (d[k][v] != SKIP_NODE))) {
                        d[u][v] = max(INT_MIN, d[u][k] + d[k][v]);
                        next[u][v] = next[u][k];
                    }
                }
            }   
        }
        for (int k = 0; k < this->n; ++k) {
            if (d[k][k] < 0) {
                vector<int> cycle;
                cycle.push_back(k + 1);
                int n = next[k][k];
                while ((n != k) && (cycle.size() < this->n + 1)) {
                    cycle.push_back(n + 1);
                    n = next[n][n];
                }
                if (cycle.size() < this->n + 1) {
                    return {true, cycle};
                }
            }
        }
        return {false, vector<int>()};
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x;
    cin >> n;
    Graph g = Graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //maybe me a connection problem
            cin >> x;
            g.w[i][j] = x; 
        }
    }
    auto res = g.find_cycle();
    if (res.first) {
        cout << "YES\n";
        cout << res.second.size() << '\n';
        for (int i = 0; i < res.second.size(); ++ i) {
            cout << res.second[i] << ' ';
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}