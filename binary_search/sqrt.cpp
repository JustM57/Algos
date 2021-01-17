#include <iostream>
#include <cmath>

using namespace std;
const double MIN_X = 0.;
const double MAX_X = 100000.;
const int IT_NUM = 38;


long double foo(long double x) {
    return (x * x + sqrt(x));
}


long double search(long double c) {
    long double l = MIN_X;
    long double r = MAX_X;
    long double m = 0.;
    for (int i = 0; i < IT_NUM; ++i) {
        m = (r + l) / 2;
        if (c < foo(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}



int main() {
    long double c = 0.;
    cout.precision(7);
    cin >> c;
    cout << search(c);
}