#include <iostream>
#include <vector>
#include <utility>


using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int** coins = new int*[n];
    pair<int, int>** amount = new pair<int, int>*[n];
    for (int i = 0; i < n; ++i) {
        coins[i] = new int[m];
        amount[i] = new pair<int, int>[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i != 0) {
                if (j > 0) {
                    if (amount[i - 1][j].first > amount[i][j - 1].first) {
                        amount[i][j].first = amount[i - 1][j].first + coins[i][j];
                        amount[i][j].second = 1;
                    } else {
                        amount[i][j].first = amount[i][j - 1].first + coins[i][j];
                        amount[i][j].second = -1;
                    }
                } else {
                    amount[i][j].first = amount[i - 1][j].first + coins[i][j];
                    amount[i][j].second = 1;
                }
            } else {
                if (j == 0) {
                    amount[i][j].first = coins[i][j];
                    amount[i][j].second = 0; 
                } else {
                    amount[i][j].first = amount[i][j - 1].first + coins[i][j];
                    amount[i][j].second = -1;
                }
            }
        }
    }
    cout << amount[n - 1][m - 1].first << '\n';
    int i = n - 1;
    int j = m - 1;
    vector<char> res;
    while ((i > 0) || (j > 0)) {
        if (amount[i][j].second == 1) {
            res.push_back('D');
            --i;
        } else {
            res.push_back('R');
            --j;
        }
    }
    for (int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
    }
    for (int i = 0; i < n; ++i) {
        delete [] coins[i];
        delete [] amount[i];
    }
    delete [] coins;
    delete [] amount;
    return 0;
}