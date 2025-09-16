// Money Sums (CSES)

#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Time: O(N * K)
// Space: O(N * K)

void allCoinCombinations(
    int curr_coin_idx,
    int curr_sum,
    vector<int>& coins,
    int coin_cnt,
    vector<vector<int>>& vis,
    set<int>& sums_set
) {
    if (curr_coin_idx == coin_cnt) {
        sums_set.insert(curr_sum);
        return;
    }
    if (vis[curr_coin_idx][curr_sum] != 0) {
        return;
    }

    vis[curr_coin_idx][curr_sum] = 1;

    // include curr_coin
    allCoinCombinations(
        curr_coin_idx+1,
        curr_sum + coins[curr_coin_idx],
        coins,
        coin_cnt,
        vis,
        sums_set
    );
    
    // exclude curr_coin
    allCoinCombinations(
        curr_coin_idx+1,
        curr_sum,
        coins,
        coin_cnt,
        vis,
        sums_set
    );
    
    vis[curr_coin_idx][curr_sum] = 2;
}

void solve(
    vector<int>& coins,
    int coin_cnt
) {
    const int MAX_SUM = 1e5;
    vector<vector<int>> vis(coin_cnt+1, vector<int>(MAX_SUM+1, 0));
    set<int> sums_set;
    allCoinCombinations(
        0,
        0,
        coins,
        coin_cnt,
        vis,
        sums_set
    );

    cout << (sums_set.size()-1) << endl;
    for (int sum : sums_set) {
        if (sum > 0) {
            cout << sum << " ";
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int coin_cnt;
    cin >> coin_cnt;

    vector<int> coins(coin_cnt);
    for (int i = 0; i < coin_cnt; i++) {
        cin >> coins[i];
    }

    solve(coins, coin_cnt);

    return 0;
}