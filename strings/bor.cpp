#include <string>
#include <iostream>
#include <vector>
 
using namespace std;
 
const int ALPHABET_SIZE = 26;
const int MAX_WORD_LEN = 30;
const int A_INT = (int)'a';
const int MAX_WORDS_SUM = 100000;


struct Node {
    int* child;
    int word_end;;
    Node() {
        word_end = -1;
        child = new int[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            child[i] = -1;
        }
    }
};
 
 
class Trie {
private:
    int size;
    vector<Node> next;
    vector<bool> words;
public:
    Trie() : size(0) {
        next.push_back(Node());
    }
 
    void insert(int idx, string s) {
        int v = 0;
        for (int i = 0; i < s.size(); ++i) {
            int char_pos = (int)s[i] - A_INT;
            if (next[v].child[char_pos] == -1) {
                ++this->size;
                next[v].child[char_pos] = this->size;
                next.push_back(Node());
            }
            v = next[v].child[char_pos];
            // cout << v << '\n';
        }
        next[v].word_end = idx;
        this->words.push_back(false);
    }
 
    void contains_podtext(string s) {
        int v = 0;
        for (int i = 0; i < s.size(); ++i) {
            int char_pos = (int)s[i] - A_INT;
            if (next[v].child[char_pos] == -1) {
                return ;
            }
            v = next[v].child[char_pos];
            if (next[v].word_end > -1) {
                this->words[next[v].word_end] = true;
            }
        }
    }
 
    int get_size() {
        return this->size;
    }
 
    vector<bool> get_result() {
        return this->words;
    }
};
 
 
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    string text, word;
    int m;
    cin >> text >> m;
    Trie trie = Trie();
    for (int i = 0; i < m; ++i) {
        cin >> word;
        trie.insert(i, word);
    }
    for (int i = 0; i < text.size(); ++i) {
        word = text.substr(i, MAX_WORD_LEN);
        trie.contains_podtext(word);
    }
    vector<bool> res = trie.get_result();
    for (int i = 0; i < m; ++i) {
        if (res[i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}