// Minimizing Coins (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
 
using namespace std;
 
// Time: O(N * K)
// Space: O(N)
 
/**
 * Infinite Knapsack Problem
 * 
 * Infinite number of coins are available
 * and you have to pick minimum number of them
 * to create target_sum
 */

const int INF = INT_MAX;

int countMinCoinsRequired(
    int curr_sum,
    vector<int>& coins,
    vector<int>& dp
) {
    if (curr_sum < 0)
        return INF;
    if (curr_sum == 0)
        return 0;
    if (dp[curr_sum] != -1)
        return dp[curr_sum];

    int min_coin_cnt = INF;
    for (int coin : coins) {
        int coin_cnt = countMinCoinsRequired(
            curr_sum-coin,
            coins,
            dp
        );
        if (coin_cnt != INF) {
            min_coin_cnt = min(
                min_coin_cnt,
                coin_cnt + 1
            );
        }
    }

    return dp[curr_sum] = min_coin_cnt;
}

void solve(
    int target_sum,
    vector<int>& coins,
    int coin_cnt
) {
    vector<int> dp(target_sum+1, -1);
    int min_coin_cnt = countMinCoinsRequired(target_sum, coins, dp);
    cout << (min_coin_cnt == INF ? -1 : min_coin_cnt) << endl;
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