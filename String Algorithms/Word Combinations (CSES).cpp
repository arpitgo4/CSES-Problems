// Word Combinations (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// N <= S.length()
// Time: O(N^2)
// Space: O(N)

const int MOD = 1e9 + 7;
const int MAX_STRING_LENGTH = 5000 + 1;
vector<int> cache(MAX_STRING_LENGTH, -1);

unordered_set<string> uSet;

int dfs(string& S, int i) {
    if (i == S.length())
        return 1;
    if (cache[i] != -1)
        return cache[i];
    
    int count = 0;
    string word = "";
    for (int j = i; j < S.length(); j++) {
        word += S[j];
        if (uSet.find(word) != uSet.end())
            count = (count + dfs(S, j+1)) % MOD;
    }

    return cache[i] = count;
}

void solve(string& S, vector<string>& A, int K) {
    uSet = unordered_set<string>(A.begin(), A.end());

    int count = dfs(S, 0);
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