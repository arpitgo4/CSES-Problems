// Coin Combinations II (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N * K)
// Space: O(N * K)

/**
 * Infinite Knapsack DP
 * 
 * Inifinite supply of coins but we have to 
 * count ordered ways in which we can create
 * desired knapsack.
 * 
 * Ordered knapsacks can be created by exhausting
 * the usage of particular coin and not re-using it for 
 * the specific knapsack later on.
 */

const int MOD = 1e9 + 7;

int countCombinations(
    int curr_sum,
    int curr_coin_idx,
    vector<int>& coins,
    int coin_cnt,
    vector<vector<int>>& dp
) {
    if (curr_sum < 0 || curr_coin_idx == coin_cnt)
        return 0;
    if (curr_sum == 0)
        return 1;
    if (dp[curr_sum][curr_coin_idx] != -1)
        return dp[curr_sum][curr_coin_idx];

    int include_coin_cnt = countCombinations(
        curr_sum - coins[curr_coin_idx],
        curr_coin_idx,
        coins,
        coin_cnt,
        dp
    );

    int exclude_coin_cnt = countCombinations(
        curr_sum,
        curr_coin_idx+1,
        coins,
        coin_cnt,
        dp
    );
    
    return dp[curr_sum][curr_coin_idx] = (
        (include_coin_cnt + exclude_coin_cnt) % MOD
    );
}

void solve(
    int target_sum,
    vector<int>& coins,
    int coin_cnt
) {
    vector<vector<int>> dp(target_sum+1, vector<int>(coin_cnt+1, -1));
    int combination_cnt = countCombinations(
        target_sum,
        0,
        coins,
        coin_cnt,
        dp
    );

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