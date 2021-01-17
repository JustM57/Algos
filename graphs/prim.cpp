#include <iostream>
#include <utility>
#include <climits>
#include <cmath>
#include <iomanip>

 
using namespace std;
 
 
class Graph {
private:
    int V;
    pair<int, int>* vertexes;
    double dist(int a, int b) {
        double x = this->vertexes[a].first - this->vertexes[b].first;
        double y = this->vertexes[a].second - this->vertexes[b].second;
        return sqrt(x * x + y * y);
    }
 
public:
    Graph(int n) : V(n){
        this->vertexes = new pair<int, int>[n];
    }; 
 
    ~Graph() {
        delete [] this->vertexes;
    };

    void add_vertex(int i, int x, int y) {
        this->vertexes[i] = {x, y};
    };
 
    void shortes_distance() {
        int* used = new int[this->V];
        double* depth = new double[this->V];
        for (int i = 0; i < this->V; ++i) {
            used[i] = 0;
            depth[i] = dist(0, i);
        }
        used[0] = 1;
        for (int i = 0; i < this->V - 1; ++i) {
            int next = -1;
            for (int v = 1; v < this->V; ++v) {
                if (((next == -1) or (depth[v] < depth[next])) and (used[v] == 0)) {
                    next = v;
                }
            }
            used[next] = 1;
            for (int v = 0; v < this->V; ++v) {
                if (used[v] == 0) {
                    depth[v] = min(depth[v], dist(v, next));
                }
            }
        }
        double ans = 0;
        for (int i = 0; i < this->V; ++i) {
            ans += depth[i];
        }
        cout << setprecision(10) << ans;
        delete [] used;
        delete [] depth;
    };
};
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Graph g = Graph(n);
    int x, y, w;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        g.add_vertex(i, x, y);
    }
    g.shortes_distance();
    return 0;
}