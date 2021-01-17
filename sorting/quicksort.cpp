#include <iostream> 
#include <time.h>
#include <algorithm>

using namespace std;


void split(int* a, int l, int r, int x, int* m1, int* m2){
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


void qsort(int* a, int l, int r){
    if (r - l > 1){
        int idx = l + (rand() % (r - l));
        int x = a[idx];
        int m1 = l;
        int m2 = l;
        split(a, l, r, x, &m1, &m2);
        qsort(a, l, m1);
        qsort(a, m2, r);
    }
}


int main()
{   
    srand(time(NULL));
    int n = 0;
    int* arr;
    cin >> n;
    arr = new int[n];
    for(int i = 0; i < n; ++i) cin >> arr[i];
    qsort(arr, 0, n);
    for(int i = 0; i < n; ++i) cout << arr[i] << ' ';
}