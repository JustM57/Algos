#include <iostream>
#include <stack>
#include <utility>


using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int* nums = new int[n];
    pair<int, int>* res = new pair<int, int>[n];
    pair<int, int> max_res = {0, 0};
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        res[i].first = 1;
        for (int j = 0; j < i; ++ j) {
            if ((nums[j] < nums[i]) && (res[j].first>= res[i].first)) {
                res[i].first = res[j].first + 1;
                res[i].second = j;
            }
        }
        if (res[i].first > max_res.first) {
            max_res.first = res[i].first;
            max_res.second = i;
        }
    }
    cout << max_res.first << '\n';
    stack<int> podposl;
    pair<int, int> num = max_res;
    for (int i = 0; i < max_res.first; ++i) {
        podposl.push(nums[num.second]);
        num = res[num.second];
    }
    for (int i = 0; i < max_res.first; ++i) {
        cout << podposl.top() << ' ';
        podposl.pop();
    }
    delete [] res;
    delete [] nums;
    return 0;
}