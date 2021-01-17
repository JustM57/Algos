#include <string>
#include <iostream>
#include <ctime>
#include <utility>
#include <vector>
 
using namespace std;


int* z_function(string s) {
    int* z = new int[s.size()];
    int left = 0;
    int right = 0;
    for (int i = 1; i < s.size(); ++ i) {
        z[i] = max(0, min(right - i, z[i - left]));
        while ((i + z[i] < s.size()) && (s[z[i]] == s[i + z[i]])) {
            ++z[i];
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}


int main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    auto z = z_function(s);
    for (int i = 1; i < s.size(); ++i) {
        cout << z[i] << ' ';
    }
    return 0;
}
