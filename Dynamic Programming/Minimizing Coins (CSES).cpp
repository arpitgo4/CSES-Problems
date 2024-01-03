// Minimizing Coins (CSES)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

// Time: O(K*N) 
// Space: O(K)

vector<int> dp;

void solve_iterative(vector<int>& C, int N, int K) {
    dp.assign(K+1, INT_MAX);
    for (int c : C)
        if (c < K+1)
            dp[c] = 1;

    // recurrence relation, dp[K] = min(dp[K], 1 + dp[K-C[i]])

    for (int k = 1; k <= K; k++) {
        for (int c : C) {
            if (k - c > 0 && dp[k-c] != INT_MAX)
                dp[k] = min(dp[k], 1 + dp[k-c]);
        }
    }

    int coins = dp[K] == INT_MAX ? -1 : dp[K];
    cout << coins;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

// Time: O(N*K)
// Space: O(K)

vector<int> cache;

int dfs(vector<int>& C, int N, int K) {
    if (K == 0)
        return 0;
    if (K < 0)
        return INT_MAX;
    if (cache[K] != -1)
        return cache[K];

    int min_coin = INT_MAX;
    for (int c : C) {
        int a = dfs(C, N, K-c);
        if (a != INT_MAX)
            a += 1;
        min_coin = min(min_coin, a);
    }

    return cache[K] = min_coin;
}

void solve_recursive(vector<int>& C, int N, int K) {
    cache.assign(K+1, -1);
    int coins = dfs(C, N, K);
    coins = (coins == INT_MAX ? -1 : coins);
    cout << coins;
}

//////////////////////////////////////////////////////////////////////////////

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<int> C(N);
    for (int i = 0; i < N; i++)
        cin >> C[i];

    // solve_recursive(C, N, K);
    solve_iterative(C, N, K);

    return 0;
}