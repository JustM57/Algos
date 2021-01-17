#include <iostream>
#include <string>


using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length();
    int m = s2.length();
    int** distance = new int*[n];
    for (int i = 0; i < n; ++i) {
        distance[i] = new int[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s1[i] == s2[j]) {
                if ((i > 0) && (j > 0)) {
                    distance[i][j] = distance[i - 1][j - 1];
                } else {
                    distance[i][j] = max(i, j);
                }
            } else {
                if (i > 0) {
                    if (j > 0) {
                        distance[i][j] = min(distance[i - 1][j - 1], min(
                            distance[i - 1][j], distance[i][j - 1])) + 1;
                    } else {
                        distance[i][j] = distance[i - 1][j] + 1;
                    }
                } else {
                    if (j == 0) {
                        distance[i][j] = 1;
                    } else {
                        distance[i][j] = distance[i][j - 1] + 1;
                    }
                }
            }
        }
    }
    cout << distance[n - 1][m - 1] << '\n';
    for (int i = 0; i < n; ++i) {
        delete [] distance[i];
    }
    delete [] distance;
    return 0;
}