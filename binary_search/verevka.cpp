#include <iostream>

using namespace std;
const long MIN_X = 0;
const long MAX_X = 10000000;


bool check(long* a, int n, int k, long m) {
    int i = 0;
    int counter = 0;
    long* a_copy = new long[n];
    for (i = 0; i < n; ++i) a_copy[i] = a[i];
    i = 0;
    // посчитаем сколько раз мы можем отрезать верёвку длины k
    while ((i < n) && (counter <= k)) {
        if (a_copy[i] >= m) {
            a_copy[i] -= m;
            ++counter;
        }
        else {
            ++i;
        }
    }
    delete [] a_copy;
    return (counter < k);
}


long lower_bound(long* a, int n, int k) {
    long l = MIN_X;
    long r = MAX_X;
    long m = 0;
    while ((r - l) > 1) {
        m = (r + l) / 2;
        if (check(a, n, k, m)) {
            r = m;
        } else {
            l = m;
        }
    }
    if (!check(a, n, k, r)) return r;
    return l;
}


int main() {
    int n;
    int k;
    cin >> n >> k;
    long* a = new long[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << lower_bound(a, n, k);
    delete [] a;
    return 0;
}
