// Coin Combinations I (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
/**
 * subset sum problem,
 * find all subsets with repeated elements which sums up to K
 * 
 * making array size smaller isn't intuitive to smaller sub problems initially.
 * Better to reduce the size of actual problem which is the amount to be broken 
 * down into coins.
*/

// Time: O(N * K)
// Space: O(K)
 
const int MOD = 1e9 + 7;
vector<int> dp;

int dfs(int K, vector<int>& coins, int N) {
    if (K < 0)
        return 0;
    if (K == 0)
        return 1;
    if (dp[K] != -1)
        return dp[K];

    int count = 0;
    for (int c : coins)
        count = (count + dfs(K-c, coins, N)) % MOD;
    
    return dp[K] = count;
}

void solve(vector<int>& coins, int N, int K) {
    dp.assign(K+1, -1);

    int count = dfs(K, coins, N);
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

    solve(coins, N, K);
    
    return 0;
}