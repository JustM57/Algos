#include <iostream>
#include <string>

using namespace std;
const int MIN_C = (int)'a';
const int MAX_C = (int)'z';
const int C_SIZE = MAX_C - MIN_C; 

int main() {
    int n = 0;
    int m = 0;
    int num = 0;
    cin >> n >> m;
    string a;
    string b;
    cin >> a >> b;
    int* b_counter = new int[C_SIZE];
    for (int j = 0; j < C_SIZE; ++j) b_counter[j] = 0;
    for (int j = 0; j < m; ++j){
        num = (int)b[j] - MIN_C;
        ++b_counter[num];
    }
    int count = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        int* a_counter = new int[C_SIZE];
        for (int j = 0; j < C_SIZE; ++j) a_counter[j] = 0;
        j = i;
        while ((j < n) && (j < i + m)) {
            num = (int)a[j] - MIN_C;
            ++a_counter[num];
            if (a_counter[num] > b_counter[num]) break;
            ++count;
            ++j;
        }
        delete [] a_counter;
    } 
    cout << count;
    return 0;
}
