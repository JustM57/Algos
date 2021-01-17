#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>


using namespace std;


int get_power(int k) {
    if (k == 0) {
        return 1;
    }
    return 2 * get_power(k - 1);
}


int main()
{
    const int DIV1 = get_power(16);
    const int DIV2 = get_power(30);
    int n, x, y;
    int32_t a;
    cin >> n >> x >> y >> a;
    int m, z, t, b0, b1, c0, c1;
    cin >> m >> z >> t >> b0;
    vector<int64_t> s(n);
    s[0] = a;
    int64_t res = 0;
    for (int i = 1; i < n; ++i) {
        a = (x * a + y) % DIV1;
        if (a < 0) {
            a += DIV1;
        }
        s[i] = s[i - 1] + a;
    }
    for (int i = 0; i < m; ++i) {
        if (i != 0) {
            b0 = (z * b1 + t) % DIV2;
            if (b0 < 0) {
                b0 += DIV2;
            }
        }
        b1 = (z * b0 + t) % DIV2;
        if (b1 < 0) {
            b1 += DIV2;
        }
        c0 = min(b0 % n, b1 % n);
        c1 = max(b0 % n, b1 % n);
        if (c0 != 0) {
            res += (s[c1] - s[c0 - 1]);
        } else {
            res += s[c1];
        }
    }
    cout << res;
    return 0;
}
