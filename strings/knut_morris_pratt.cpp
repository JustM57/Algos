#include <string>
#include <iostream>
#include <vector>
 
using namespace std;


int* p_function(string s) {
    int* p = new int[s.size()];
    p[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int k = p[i - 1];
        while ((k > 0) && (s[i] != s[k])) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2, s;
    cin >> s1 >> s2;
    s = s1 + "#" + s2;
    auto p = p_function(s);
    vector<int> res;
    for (int i = s1.size(); i < s.size(); ++i) {
        if (p[i] == s1.size()) {
            res.push_back(i - 2 * s1.size() + 1);
        }
    }
    cout << res.size() << '\n';
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << ' ';
    }
    return 0;
}
