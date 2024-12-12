// Word Combinations (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N^2)
// Space: O(N^2)

/**
 * Solution using a Trie and DP can be implemented in two ways,
 * 1. Use single dimension for memory and DP algorithm for subsequences
 *    with loop in recursive function.
 *    Above will yeild,
 *    Time: O(N^2)
 *    Space: O(N)
 * 
 *    Implementation: https://cses.fi/problemset/result/11405663/
 * 
 * 2. Run along the Trie and take all possible choices based on char from 
 *    given string. This will yield,
 *    Time: O(N^2)
 *    Space: O(N^2)
 */

const int MOD = 1e9 + 7;
const int ALPHABET_SZ = 26;

int counter = 0;
vector<vector<int>> dp;

class TrieNode {
public:
    bool is_word;
    vector<TrieNode*> children;
    int index;

    TrieNode() {
        this->is_word = false;
        this->children.assign(ALPHABET_SZ, NULL);
        this->index = counter++;
    }
};

TrieNode root;

void insert_trie(string& S) {
    TrieNode* node = &root;
    for (char c : S) {
        int idx = c - 'a';
        if (node->children[idx] == NULL)
            node->children[idx] = new TrieNode();

        node = node->children[idx];
    }

    node->is_word = true;
}

int dfs(int i, TrieNode* node, string& S, int N) {
    if (i == N)
        return node->is_word ? 1 : 0;
    if (dp[i][node->index] != -1)
        return dp[i][node->index];
    
    int idx = S[i] - 'a';
    TrieNode* child = node->children[idx];
    if (child == NULL)
        return 0;

    int count = 0;
    if (child->is_word)
        count = (count + dfs(i+1, &root, S, N)) % MOD;

    count = (count + dfs(i+1, child, S, N)) % MOD;
    
    return dp[i][node->index] = count;
}

void solve(string& S, vector<string>& A, int K) {
    int N = S.length();
    dp.assign(N+1, vector<int>(N+1, -1));

    for (string& w : A)
        insert_trie(w);

    int count = dfs(0, &root, S, N);
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