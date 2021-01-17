#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
const int MIN_C = (int)'a';
const int MAX_C = (int)'z';
const int C_SIZE = MAX_C - MIN_C; 


void count_sort(int n, int* p_a, const char* ch) {
    int* counter = new int[C_SIZE];
    for (int i = 0; i < C_SIZE; ++i) counter[i] = 0;
    for (int i = 0; i < n; ++i) ++counter[((int)ch[i] - MIN_C)];
    int* cumsum = new int[C_SIZE];
    for (int i = 1; i < C_SIZE; ++i) cumsum[i] = cumsum[i - 1] + counter[i - 1];
    int* p_new = new int[n];
    int num = 0;
    for (int i = 0; i < n; ++i) {
        num = (int)ch[i] - MIN_C;
        p_new[cumsum[num]] = p_a[i];
        ++cumsum[num];
    }
    for (int i = 0; i < n; ++i) p_a[i] = p_new[i];
    delete [] counter;
    delete [] cumsum;
    delete [] p_new;
}


int main() {
    int n = 0;
    int m = 0;
    int k = 0;
    cin >> n >> m >> k;
    string* a = new string[n];
    int* p_a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p_a[i] = i;
    }
    for (int i = m - 1; i >= m - k; --i) {
            char* ch = new char[n];
            for (int j = 0; j < n; ++j) ch[j] = a[p_a[j]][i];
            count_sort(n, p_a, ch);
            delete [] ch;
    } 
    for (int i = 0; i < n; ++i) cout << (a[p_a[i]]) << '\n';
    return 0;
}