#include <iostream> 

using namespace std;


void merge(int* a, int size, int med){
    //копируем first part of массив a
    int* tmp_arr = new int[med];
    for (int i = 0; i < med; ++i){
        tmp_arr[i] = a[i];
    }
    int i = 0;
    int j = 0;
    while (i + j < size){
        if ((j == size - med) or (i < med and tmp_arr[i] < a[med + j])){
            a[i + j] = tmp_arr[i];
            ++i;
        }
        else{
            a[i + j] = a[med + j];
            ++j;
        }
    }
    delete [] tmp_arr;
}


void merge_sort(int* a, int size){
    if (size > 1){
        int med = size / 2;
        merge_sort(a, med);
        merge_sort(a + med, size - med);
        merge(a, size, med);
    }
}


int main()
{
    int n = 0;
    int* arr;
    cin >> n;
    arr = new int[n];
    for(int i = 0; i < n; ++i) cin >> arr[i];
    merge_sort(arr, n);
    for(int i = 0; i < n; ++i) cout << arr[i] << ' ';
}