#include <iostream> 
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
const int INF = numeric_limits<int>::max();

class Heap {
    private:
    vector<pair<int, int>> a;
    int counter;

    public:
    Heap() {
        a = vector<pair<int, int>>(0); //val & it
        counter = 0;
    }

    void insert(int val) {
        ++counter;
        int i = a.size();
        int j;
        pair<int, int> res = {val, counter};
        a.push_back(res);
        while (i > 0) {
            j = (i - 1) / 2;
            if (a[i].first < a[j].first) {
                swap(a[i], a[j]);
            }
            i = j;
        }
    }

    pair<int, int> extract_min() {
        ++counter;
        int cur, left, right, new_i;
        int i = a.size() - 1;
        pair<int, int> res = a[0];
        swap(a[0], a[i]);
        i = 0;
        a.pop_back();
        new_i = i;
        while (2 * i + 1 < a.size()) {
            cur = a[i].first;
            left = a[2 * i + 1].first;
            if (2 * i + 2 == a.size()) {
                right = INF; 
            } else right = a[2 * i + 2].first;
            if ((left <= right) && (left < cur)) {
                swap(a[i], a[2 * i + 1]);
                new_i = 2 * i + 1;
            } else {
                if ((right < left) && (right < cur)) {
                    swap(a[i], a[2 * i + 2]);
                    new_i = 2 * i + 2;
                }
            }
            if (i != new_i) {
                i = new_i;
            } else break;
        }
        return res;
    }

    long heap_size() {return a.size(); }

    void decrease_key(int m, int n) {
        ++counter;
        int i, j;
        i = 0;
        while ((i<a.size()) && (m != a[i].second)) ++i;
        if (i < a.size()) {
            if (a[i].first > n) a[i].first = n;
            while (i > 0) {
                j = (i - 1) / 2;
                if (a[i].first < a[j].first) {
                    swap(a[i], a[j]);
                }
                i = j;
            }
        }
    }

    void increase_counter() {
        ++counter;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    pair<int, int> res;
    string word;
    Heap heap = Heap();
    while (cin >> word) {
        if (word == "push") {
            cin >> m;
            heap.insert(m);
        } else if (word == "extract-min") {
            if (heap.heap_size() == 0) {
                heap.increase_counter();
                cout << '*' << '\n';
            } else {
                res = heap.extract_min();
                cout << res.first << ' ' << res.second << '\n';
            }
        } else if (word == "decrease-key") {
            cin >> m >> n;
            heap.decrease_key(m, n);
        }
    }
    return 0;
}