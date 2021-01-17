#include <iostream>
#include <cstdint>
#include <vector>


using namespace std;


class FenvikTree {
private:
    int64_t* T;
    int n;

    int F(int i) {
        return i & (i + 1);
    }

    int64_t get(int i) {
        int64_t res = 0;
        while (i >= 0) {
            res += T[i];
            i = F(i) - 1;
        }
        return res;
    }
public:
    FenvikTree(int* a, int n_) {
        int64_t res;
        this->n = n_;
        int64_t* t = new int64_t[this->n];
        for (int i = 0; i < this->n; ++i) {
            res = 0;
            for (int j = F(i); j <= i; ++j) {
                res += a[j];
            }
            t[i] = res;    
        }
        this->T = t;
    }

    ~FenvikTree() {
        delete [] this->T;
    };

    void add(int i, int x) {
        int j = i;
        while (j < this->n) {
            this->T[j] += x;
            j = j | (j + 1);
        }
    }

    int64_t rsq(int l, int r) {
        if (l == 0) {
            return get(r);
        }
        return get(r) - get(l - 1);
    };
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int i, x, j, d;
    FenvikTree tree = FenvikTree(a, n);
    string word;
    while (cin >> word) {
        if (word == "sum") {
            cin >> i >> j;
            cout << tree.rsq(i - 1, j - 1) << '\n';
        } else {
            cin >> i >> x;
            d = x - a[i - 1];
            a[i - 1] = x;
            tree.add(i - 1, d);
        }
    }
    delete a;
    return 0;
}
