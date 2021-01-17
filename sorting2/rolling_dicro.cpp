#include <iostream>
#include <string>

using namespace std;
const int MIN_C = (int)'a';
const int MAX_C = (int)'z';
const int C_SIZE = 26; 

int main() {
    int n = 0;
    int m = 0;
    int num = 0;
    int tmp = 0;
    cin >> n >> m;
    string a;
    string b;
    cin >> a >> b;
    uint32_t* b_counter [C_SIZE] = {};
    for (uint32_t j = 0; j < m; ++j){
        num = (int)b[j] - MIN_C;
        ++b_counter[num];
    }
    uint64_t count = 0;
    uint32_t j = 0;
    uint64_t a_size = 0;
    uint32_t* a_counter [C_SIZE] = {};
    for (uint32_t i = 0; i < n; ++i) {
        num = (int)a[i] - MIN_C;
        ++a_counter[num];
        ++a_size;
        while ((j <= i) && ((a_counter[num] > b_counter[num]) || (a_size > m))) {
            tmp = (int)a[j] - MIN_C;
            --a_counter[tmp];
            --a_size;
            ++j;
        }
        count += a_size;
    } 
    cout << count;
    return 0;
}