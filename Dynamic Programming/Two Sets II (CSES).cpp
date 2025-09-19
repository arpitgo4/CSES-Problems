// Two Sets II (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N ^3)
// Space: O(N ^3)
 
using ll_t = long long;

const int MOD = 1e9 + 7;

ll_t getExponent(ll_t num, ll_t pow) {
    if (pow == 1) {
        return num;
    } else if (pow % 2 == 0) {
        return getExponent((num  * 1ll * num) % MOD, pow / 2);
    } else {                          // pow % 2 == 1
        return num * getExponent((num  * 1ll * num) % MOD, (pow-1) / 2) % MOD;
    }
}

int countSubsetsWithTargetSum(
    int curr_num,
    int num_cnt,
    ll_t target_sum,
    vector<vector<ll_t>>& dp
) {
    if (target_sum == 0) {
        return 1;
    }
    if (target_sum < 0 || curr_num > num_cnt) {
        return 0;
    }
    if (dp[curr_num][target_sum] != -1) {
        return dp[curr_num][target_sum];
    }
    
    // include curr_num
    int include_ways = countSubsetsWithTargetSum(
        curr_num + 1,
        num_cnt,
        target_sum - curr_num,
        dp
    );

    // exclude curr_num
    int exclude_ways = countSubsetsWithTargetSum(
        curr_num + 1,
        num_cnt,
        target_sum,
        dp
    );

    return dp[curr_num][target_sum] = (
        include_ways + exclude_ways
    ) % MOD;
}

void solve(
    int num_cnt
) {
    ll_t total_sum = (num_cnt) * (num_cnt+1) / 2;
    if (total_sum % 2 != 0) {
        cout << 0 << endl;
        return;
    }

    ll_t target_sum = total_sum / 2;
    vector<vector<ll_t>> dp(num_cnt+1, vector<ll_t>(total_sum+1, -1));
    ll_t subset_cnt = countSubsetsWithTargetSum(
        1,
        num_cnt,
        target_sum,
        dp
    );
    ll_t inv_2 = getExponent(2, MOD-2);
    int mod_subset_cnt = (subset_cnt * inv_2) % MOD;
    cout << mod_subset_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_cnt;
    cin >> num_cnt;
    
    solve(num_cnt);
    
    return 0;
}