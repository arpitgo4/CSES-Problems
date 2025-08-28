// Dice Combinations (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
const int MOD = 1e9 + 7;

int countCombinations(
    int curr_sum,
    vector<int>& dp
) {
    if (curr_sum < 0)
        return 0;
    if (curr_sum == 0)
        return 1;
    if (dp[curr_sum] != -1)
        return dp[curr_sum];

    int ways_cnt = 0;
    for (int dice_face = 1; dice_face <= 6; dice_face++) {
        int count = countCombinations(curr_sum-dice_face, dp);
        ways_cnt = (ways_cnt + count) % MOD;
    }
    
    return dp[curr_sum] = ways_cnt;
}

void solve(
    int target_sum
) {
    vector<int> dp(target_sum+1, -1);
    int combination_cnt = countCombinations(target_sum, dp);
    cout << combination_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int target_sum;
    cin >> target_sum;

    solve(target_sum);
    
    return 0;
}