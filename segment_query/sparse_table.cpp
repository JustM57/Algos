#include <iostream>
#include <vector>

using namespace std;


vector<int> generate_log(int n) {
    vector<int> res;
    int a = 1;
    int num = 0;
    res.push_back(num);
    for (int i = 1; i <= n; ++i) {
        if (i == a * 2) {
            a *= 2;
            num += 1;
            res.push_back(num);
        } else {
            res.push_back(num);
        }
    }
    return res;
}

vector<int> generate_power(int n) {
    vector<int> res;
    int power = 1;
    for (int i = 0; i < n; ++i) {
        res.push_back(power);
        power *= 2;
    }
    return res;
}


int main() {
    int n, m, a;
    cin >> n >> m >> a;
    int u, v;
    cin >> u >> v;
    int k, r, c1, c2;
    vector<vector<int>> mins(n);
    vector<int> log = generate_log(n);
    int start, max_power;
    for (int i = 0; i < n; ++i) {
        if (i != 0) {
            a = (23 * a + 21563) % 16714589;
        } 
        for (int j = 1; j <= i + 1; j *= 2) {
            k = log[j];
            start = i - j + 1;
            if (j == 1) {
                mins[start].push_back(a);
            } else {
                mins[start].push_back(min(mins[start][k - 1], mins[start + j / 2][k - 1]));
            }
        }
    }
    vector<int> power = generate_power(log[n] + 1);
    for (int i = 0; i < m; ++i) {
        if (i != 0) {
            u = ((17 * u + 751 + r + 2 * i) % n) + 1;
            v = ((13 * v + 593 + r + 5 * i) % n) + 1;
        }
        c1 = min(u, v) - 1;
        c2 = max(u, v) - 1;
        k = log[c2 - c1 + 1];
        max_power = power[k];
        r = min(mins[c1][k], mins[c2 - max_power + 1][k]);
        // cout << c1 << ' ' << c2 << ' ' << r << '\n';
    }
    cout << u << ' ' << v << ' ' << r << '\n';
    return 0;
}
