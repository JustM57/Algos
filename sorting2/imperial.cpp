#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;


void split(int* a, int l, int r, int x, int* m1, int* m2) {
    for (int i = l; i < r; ++i){
        if (a[i] <= x){
            if (a[i] < x){
                swap(a[i], a[*m1]);
                ++(*m1);
            }
            if (a[i] == x){
                swap(a[i], a[*m2]);
            }
            ++(*m2);
        }
    }
}


int find_k(int* a, int k, int l, int r) {
    if (r - l > 1){
        int idx = l + (rand() % (r - l));
        int x = a[idx];
        int m1 = l;
        int m2 = l;
        split(a, l, r, x, &m1, &m2);
        if (k < m1) return find_k(a, k, l, m1);
        if (k >= m2) return find_k(a, k, m2, r);
    }
    return a[k];
}


int main() {   
    srand(time(NULL));
    int n = 0;
    int m = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int* arr;
    cin >> n;
    arr = new int[n];
    for (int idx = 0; idx < n; ++idx) cin >> arr[idx];
    cin >> m;
    for (int idx = 0; idx < m; ++idx) {
        cin >> i >> j >> k;
        --i;
        --k;
        int* a_copy = new int[j - i];
        for (int it = 0; it < j - i; ++it) a_copy[it] = arr[i + it];
        cout << find_k(a_copy, k, 0, j - i) << '\n';
        delete [] a_copy;
    }
}