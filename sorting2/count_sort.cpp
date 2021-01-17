#include <iostream>
#include <string>
#include <sstream>
#include <cctype> 

using namespace std;


int main() {
    string num_str;
    getline(cin, num_str);
    stringstream extract;
    extract << num_str;
    int num = 0;
    int counter[101] = { };
    while(extract >> num) {
        ++counter[num];
	}
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < counter[i]; ++j) cout << i << ' ';
    }
    return 0;
}
