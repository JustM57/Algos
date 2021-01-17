#include <iostream> 

using namespace std;


void merge(int * a, int size, int med, long* inv){
    //копируем first part of массив a
    int* tmp_arr = new int[med];
    for (int i=0; i<med; ++i){
        tmp_arr[i] = a[i];
    }
    int i = 0;
    int j = 0;
    while (i + j < size){
        if ((j == size - med) || ((i < med) && (tmp_arr[i] <= a[med+j]))){
            a[i + j] = tmp_arr[i];
            ++i;
        }
        else{
            if (j < size-med){
                a[i + j] = a[med+j];
                *inv += med-i;
                ++j;
            }
        }
    }
}


void merge_sort(int* a, int size, long* inv){
    if (size > 1){
        int med = size / 2;
        merge_sort(a, med, inv);
        merge_sort(a+med, size-med, inv);
        merge(a, size, med, inv);
    }
}


int main()
{
    int n = 0;
    int * arr;
    long inv = 0;
    cin >> n;
    arr = new int[n];
    for(int i=0; i<n; ++i) cin >> arr[i];
    merge_sort(arr, n, &inv);
    cout << inv;
}