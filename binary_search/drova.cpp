#include <iostream>
#include <algorithm>
#include <cmath>


using namespace std;
const double MIN_X = 0.;
const double MAX_X = 1.;
const int IT_NUM = 34;


double check(double a, double x, int vp, int vf) {
    double f = sqrt(a * a + (1 - x) * (1 - x)); //расстояние по лесу
    double p = sqrt((1 - a) * (1 - a) + x * x); //расстояние по полю
    return f / vf + p / vp;
}


double time(double a, int vp, int vf) {
    double l = MIN_X;
    double r = MAX_X;
    double m1 = 0;
    double m2 = 0;
    for (int i = 0; i < IT_NUM; ++ i) {
        m1 = (2 * l + r) / 3;
        m2 = (l + 2 * r) / 3;
        if (check(a, m1, vp, vf) < check(a, m2, vp, vf)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return r;
}


int main() {
    double a = 0;
    int vp = 0;
    int vf = 0;
    cin >> vp >> vf >> a;
    cout.precision(5);
    cout << time(a, vp, vf);
    return 0;
}
