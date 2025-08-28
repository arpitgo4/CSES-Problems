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

/**
 * Infinite Knapsack DP Problem
 * 
 * Infinite supply for coins and we need to fill the
 * knapsack (subset) with coins to reach the desired sum.
 * 
 * Count how many ways target (how many subsets) can be formed.
 */

// Time: O(N * K)
// Space: O(K)

const int MOD = 1e9 + 7;

int countCombinations(
    int curr_sum,
    vector<int>& coins,
    vector<int>& dp
) {
    if (curr_sum < 0)
        return 0;
    if (curr_sum == 0)
        return 1;
    if (dp[curr_sum] != -1)
        return dp[curr_sum];

    int ways_cnt = 0;
    for (int coin : coins) {
        int comb_cnt = countCombinations(curr_sum-coin, coins, dp);
        ways_cnt = (ways_cnt + comb_cnt) % MOD;
    }

    return dp[curr_sum] = ways_cnt;
}

void solve(
    int target_sum,
    vector<int>& coins,
    int coin_cnt
) {
    vector<int> dp(target_sum+1, -1);
    int combination_cnt = countCombinations(target_sum, coins, dp);
    cout << combination_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int coin_cnt, target_sum;
    cin >> coin_cnt >> target_sum;

    vector<int> coins(coin_cnt);
    for (int i = 0; i < coin_cnt; i++) {
        cin >> coins[i];
    }

    solve(
        target_sum,
        coins,
        coin_cnt
    );
    
    return 0;
}