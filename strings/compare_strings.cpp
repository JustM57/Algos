#include <string>
#include <iostream>
#include <ctime>
#include <utility>
#include <vector>
 
using namespace std;
 
const uint32_t MAX_P_MULT = 100;
const uint32_t SIMPLE_SIZE = 26;
const uint32_t SIMPLE[SIMPLE_SIZE] = {
    31, 29 ,1597, 2897, 5741, 7561, 28657, 33461, 43261, 
    96557, 426389, 514229, 4713, 5795, 6611, 18496, 32292, 32469,
    59656, 90825, 262419, 361275, 481899, 1354828, 6328548, 6679881
};
 
 
 
pair<uint32_t*, uint32_t*> init_hash_power(string s, uint32_t p) {
    uint32_t* ppow = new uint32_t[s.size()];
    uint32_t* hash = new uint32_t[s.size()];
    ppow[0] = 1;
    hash[0] = (uint32_t)s[0];
    for (uint32_t i = 1; i < s.size(); ++i) {
        ppow[i] = ppow[i - 1] * p;
        hash[i] = hash[i - 1] * p + (uint32_t)s[i];
    }
    return {hash, ppow};
}
 
 
uint32_t init_hash_params(uint32_t n) {
    srand(time(NULL));
    uint32_t p = 1;
    while ((p < n) || (p > n * MAX_P_MULT)) {
        p = SIMPLE[rand() % SIMPLE_SIZE];
    }
    return p;
}
 
 
uint32_t get_hash(uint32_t l, uint32_t r, uint32_t* hash, uint32_t* ppow) {
    if (l == 0) {
        return hash[r];
    }
    return hash[r]  - (ppow[r - l + 1] * hash[l - 1]);
}
 

bool is_equal(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t* hash, uint32_t* ppow, string s) {
    if (get_hash(a, b, hash, ppow) == get_hash(c, d, hash, ppow)) {
        for (int i = a; i <= b; ++i) {
            if (s[i] != s[c - a + i]) {
                return false;
            }
            return true;
        }
    }
    return false;
}
 
 
int main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    uint32_t m, a, b, c, d;
    cin >> s >> m;
    auto params = init_hash_params(s.size());
    auto converter = init_hash_power(s, params);
    for (uint32_t i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        if (is_equal(--a, --b, --c, --d, converter.first, converter.second, s)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
