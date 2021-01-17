#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <string>
#include <algorithm>


using namespace std;
const int DEFAULT_SIZE = 0;


class Graph {
private:
    map<string, vector<string>> edges;
    vector<string> vertices;
    string root;

    void dfs(string v, map<string, int>* length, int cur) {
        ++cur;
        (*length)[v] = cur;
        vector<string> vertex = this->edges[v];
        for (const auto& u: vertex) {
            if ((*length)[u] == 0) {
                dfs(u, length, cur);
            }
        }
    };

public:
    void add(string x, string y) {
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        transform(y.begin(), y.end(), y.begin(), ::tolower);
        this->vertices.push_back(y);
        this->vertices.push_back(x);
        this->edges[y].push_back(x);
    };

    pair<int, map<string, int>> get_max_length() {
        map<string, int> length;
        int max_l = DEFAULT_SIZE;
        for (const auto& v: this->vertices) {
            if (length[v] == DEFAULT_SIZE) {
                dfs(v, &length, DEFAULT_SIZE);
            }
            if (length[v] > max_l) {
                max_l = length[v];
            }
        }
        return {max_l, length};
    };
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string name1, name2, tmp;
    Graph g = Graph();
    for (int i = 0; i < n; ++i) {
        cin >> name1 >> tmp >> name2;
        g.add(name1, name2);
    } 
    auto res = g.get_max_length();
    cout << res.first << '\n';
    // for (auto const& x : res.second) {
    //     cout << x.first << ' ' << x.second << '\n' ;
    // }
    return 0;
}