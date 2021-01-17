#include <iostream>
#include <algorithm>

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


int32_t binary_search(int32_t* a, int n, int32_t kl, int32_t ku) {
    int lb = lower_bound(a, n, kl);
    int ub = lower_bound(a, n, ku + 1);
    return max(0, (ub - lb));
}


int main() {
    int n = 0;
    cin >> n;
    int32_t* a = new int32_t[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, a + n);
    int k = 0;
    int32_t kl = 0;
    int32_t ku = 0;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> kl >> ku;
        cout << binary_search(a, n, kl, ku) << ' ';
    }
    delete [] a;
    return 0;
}
