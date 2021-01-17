#include <iostream>

using namespace std;


int lower_bound(int32_t* a, int r, int32_t k) {
    int l = -1;
    int m = 0;
    while ((r - l) > 1) {
        m = (r + l) / 2;
        if (k <= a[m]) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}


int32_t binary_search(int32_t* a, int n, int32_t k) {
    int lb = lower_bound(a, n, k);
    if ((lb == n) || ((lb > 0) && ((k - a[lb - 1]) <= (a[lb] - k)))) {
        return a[lb - 1];
    }
    return a[lb];
}


int main() {
    int n = 0;
    int k = 0;
    int32_t ki = 0;
    cin >> n >> k;
    int32_t tmp = 0;
    int32_t* a = new int32_t[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> ki;
        cout << binary_search(a, n, ki) << '\n';
    }
    delete [] a;
    return 0;
}
