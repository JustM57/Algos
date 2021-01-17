#include <iostream> 

using namespace std;

int main(){
    unsigned t = 0;
    int a = 0;
    int b = 0;
    cin >> t;
    for (int i = 0; i < t; ++i){
        cin >> a >> b;
        cout << a + b << '\n';
    }
    return 0;
}