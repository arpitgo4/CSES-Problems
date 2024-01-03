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
const int MAX_WORD_LENGTH = 1e6 + 1;
const int MAX_STRING_LENGTH = 5000 + 1;
const int ALPHABET_SIZE = 26;

vector<int> cache(MAX_STRING_LENGTH, -1);
vector<vector<int>> trie(MAX_WORD_LENGTH, vector<int>(ALPHABET_SIZE, 0));

void print_vector(vector<vector<int>>& A, int depth) {
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++)
            cout << A[i][j] << ", ";
        cout << endl;
    }
}

// 0: no char
// 1: char present
// 2: char ends in word
void insert_word(string& word) {
    int depth = 0, idx = 0;
    for (char c : word) {
        idx = c - 'a';
        if (trie[depth][idx] == 0)
            trie[depth][idx] = 1;

        depth++;
    }

    trie[depth-1][idx] = 2;
}

int dfs(int i, string& S, int N) {
    if (i == N)
        return 1;
    if (cache[i] != -1)
        return cache[i];
    
    int count = 0, trie_depth = 0;
    for (int j = i; j < N; j++) {
        int idx = S[j] - 'a';
        int val = trie[trie_depth][idx];
        if (val == 0)
            break;

        if (val == 2)
            count = (count + dfs(j+1, S, N)) % MOD;

        trie_depth++;
    }

    return cache[i] = count;
}

void solve(string& S, vector<string>& A, int K) {
    int N = S.length();
    for (string& s : A) {
        string sub = s.substr(0, N); 
        insert_word(sub);
    }

    print_vector(trie, 5);

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