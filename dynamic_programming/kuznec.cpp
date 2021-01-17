#include <iostream>
#include <vector>
#include <utility>


using namespace std;
const int MIN_INT = -2147483648;


void add_income(int* coins, int* amount, int n, int k){
    int max_income = MIN_INT;
    for (int i = 1; i < k + 1; ++i) {
        if (n - i > 0) {
            if (amount[n - i] == MIN_INT) {
                add_income(coins, amount, n - i, k);
            }
            if (coins[n] + amount[n - i] > max_income) {
                max_income = coins[n] + amount[n - i];
            }
        } else {
            break;
        }
    }
    amount[n] = max_income;
}

void find_income(int* coins, int* amount, vector<int>* jumps, int n, int k) {
    int max_income = MIN_INT;
    int best = 0;
    for (int i = 1; i < k + 1; ++i) {
        if (n - i > 0) {
            if (coins[n] + amount[n - i] > max_income) {
                best = n - i;
                max_income = coins[n] + amount[n - i];
            }
        } else {
            break;
        }
    }
    jumps->push_back(n);
    if (best > 0) {
        find_income(coins, amount, jumps, best, k);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int* coins = new int[n + 1];
    coins[1] = 0;
    coins[n] = 0;
    for (int i = 2; i < n; ++i) {
        cin >> coins[i];
    }
    int* amount = new int[n + 1];
    vector<int>* jumps = new vector<int>;
    amount[1] = 0;
    for (int i = 2; i <= n; ++i) {
        amount[i] = MIN_INT;
    }
    add_income(coins, amount, n, k);
    find_income(coins, amount, jumps, n, k);
    cout << amount[n] << '\n';
    cout << jumps->size() - 1 << '\n';
    for (int i = jumps->size() - 1; i >=0 ; --i) {
        cout << (*jumps)[i];
        if (i != 0) {
            cout << ' ';
        }
    }
    delete [] coins;
    delete [] amount;
    return 0;
}