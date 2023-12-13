// Word Combinations (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// N = S.length()
// K = number of words in dictionary
// M = max length of any word
// Time: O(N^2 + 26*M) ~ O(N^2 + M)
// Space: O(26*M) ~ O(M)
 
const int MOD = 1e9 + 7;
const int MAX_STRING_LENGTH = 5000 + 1;
vector<int> cache(MAX_STRING_LENGTH, -1);
 
class TrieNode {
public:
    vector<TrieNode*> children;
    bool isWord;
 
    TrieNode() {
        this->isWord = false;
        this->children.assign(26, NULL);
    }
};
 
class Trie {
public:
    
    TrieNode* root;
 
    Trie() {
        this->root = new TrieNode();
    }
 
    TrieNode* getRoot() {
        return this->root;
    }
 
    void insert(string& S) {
        TrieNode* node = root;
        for (char c : S) {
            int idx = c - 'a';
            if (node->children[idx] == NULL)
                node->children[idx] = new TrieNode();
 
            node = node->children[idx];
        }
 
        node->isWord = true;
    }
} trie;
 
int dfs(int i, string& S, int N) {
    if (i == N)
        return 1;
    if (cache[i] != -1)
        return cache[i];
    
    int count = 0;
    TrieNode* node = trie.getRoot();
    for (int j = i; j < N; j++) {
        int idx = S[j] - 'a';
        node = node->children[idx];
        if (node == NULL)
            break;
 
        if (node->isWord)
            count = (count + dfs(j+1, S, N)) % MOD;
    }
 
    return cache[i] = count;
}
 
void solve(string& S, vector<string>& A, int K) {
    int N = S.length();
    for (string& s : A) {
        string sub = s.substr(0, N); 
        trie.insert(sub);
    }
 
    int count = dfs(0, S, N);
    cout << count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;
 
    int K;
    cin >> K;
 
    vector<string> A(K);
    for (int i = 0; i < K; i++)
        cin >> A[i];
 
    solve(S, A, K);
 
    return 0;
} 