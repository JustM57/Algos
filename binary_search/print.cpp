#include <iostream>
#include <algorithm>


using namespace std;
const long MIN_X = 0;


long check(long n, long k, int x, int y) {
    return max(k * x, (n - k) * y);
}


long time(long n, int x, int y) {
    long l = MIN_X;
    long r = n;
    long m1 = 0;
    long m2 = 0;
    while ((r - l) > 2) {
        m1 = (2 * l + r) / 3;
        m2 = (l + 2 * r) / 3;
        if (check(n, m1, x, y) < check(n, m2, x, y)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    long res = min(check(n, r, x, y), check(n, l, x, y));
    res = min(check(n, r, x, y), check(n, r - 1, x, y));
    return res;
}


int main() {
    long n = 0;
    int x = 0;
    int y = 0;
    cin >> n >> x >> y;
    if (y < x) swap(x, y);
    cout << x + time(n - 1, x, y);
    return 0;
}
