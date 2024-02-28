// Coin Combinations II (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N * K)
// Space: O(N * K)
  
const int MOD = 1e9 + 7;
vector<vector<int>> dp;

void print_vector(vector<vector<int>>& A) {
    for (auto& v : A) {
        for (int a : v)
            cout << a << " ";
        cout << endl;
    }
}

// wrong result on some test cases...!!!
void solve_iter(vector<int>& coins, int N, int K) {
    dp.assign(N, vector<int>(K+1, 0));
    for (int j = 1; j <= K; j++)
        dp[0][j] = (j % coins[0] == 0 ? 1 : 0);
    for (int i = 0; i < N; i++)
        dp[i][0] = 1;
    
    for (int i = 1; i < N; i++)
        for (int j = 2; j <= K; j++) {
            dp[i][j] += dp[i-1][j];                                     // not using current coin, re-using result for the subproblem without current coin available.
            if (j-coins[i] >= 0)
                dp[i][j] = (dp[i][j] + dp[i][j-coins[i]]) % MOD;        // using current coin and re-using result for the subproblem where coins available is same but amount is lesser
        }

    cout << dp[N-1][K];
}

// recursive impl. gives stack-overflow for big value of K and small values of coins
int dfs(int i, int K, vector<int>& coins, int N) {
    if (K == 0)
        return 1;    
    if (K < 0)
        return 0;
    if (dp[i][K] != -1)
        return dp[i][K];

    int count = 0;
    for (int idx = i; idx < N; idx++)
        count = (count + dfs(idx, K-coins[idx], coins, N)) % MOD;

    return dp[i][K] = count;
}

void solve(vector<int>& coins, int N, int K) {
    dp.assign(N, vector<int>(K+1, -1));

    int count = dfs(0, K, coins, N);
    cout << count;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    cin >> N >> K;

    vector<int> coins(N);
    for (int i = 0; i < N; i++)
        cin >> coins[i];

    solve_iter(coins, N, K);
    
    return 0;
}