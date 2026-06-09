// Distinct Numbers (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(1)

/**
 * Hash-Tables offers O(N) time complexity on AVERAGE.
 * With high number of collisions, it can degrade to O(N^2).
 * 
 * So, dependent on the test case, hash-table can give poor
 * performance. But, sorting is much more stable and outshine
 * it in real-world.
 */

void solve(
    vector<int>& nums,
    int num_cnt
) {
    sort(nums.begin(), nums.end());

    int distinct_cnt = 1;
    for (int i = 1; i < num_cnt; i++) {
        if (nums[i-1] != nums[i]) {
            distinct_cnt++;
        }
    }

    cout << distinct_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_cnt;
    cin >> num_cnt;
    
    vector<int> nums(num_cnt);
    for (int i = 0; i < num_cnt; i++) {
        cin >> nums[i];
    }

    solve(nums, num_cnt);
    
    return 0;
}