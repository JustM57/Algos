#include <iostream>
#include <algorithm> 

using namespace std;


void sort(int* a, int size){
    for (int i = 1; i < size; ++i){
        int j = i;
        while ((j > 0) && (a[j - 1] > a[j])){
            swap(a[j - 1], a[j]);
            --j;
        }
    }
}


int main()
{
    int n = 0;
    int* arr;
    cin >> n;
    arr = new int[n];
    for(int i = 0; i < n; ++i) cin >> arr[i];
    sort(arr, n);
    for(int i = 0; i < n; ++i) cout << arr[i] << ' ';
}