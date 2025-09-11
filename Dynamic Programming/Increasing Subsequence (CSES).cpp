// Increasing Subsequence (CSES)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

/**
 * subseq[l] -> it is the smallest element at which an increasing
 *          subsequence of length `l` ends.
 */

int findLongestIncreasingSubseq(
    vector<int>& nums,
    int num_cnt
) {
    vector<int> subseq;
    for (int i = 0; i < num_cnt; i++) {
        int j = lower_bound(
            subseq.begin(),
            subseq.end(),
            nums[i]
        ) - subseq.begin();

        if (j == (int) subseq.size()) {
            subseq.push_back(nums[i]);
        } else {
            subseq[j] = nums[i];
        }
    }

    return subseq.size();
}

void solve(
    vector<int>& nums,
    int num_cnt
) {
    int max_subseq_len = findLongestIncreasingSubseq(
        nums,
        num_cnt
    );

    cout << max_subseq_len << endl;
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