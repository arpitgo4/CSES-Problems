// Increasing Subsequence (CSES)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

/**
 * dp[l] -> it is the smallest element at which an increasing
 *          subsequence of length `l` ends.
 */

void solve(vector<int>& A, int N) {
    vector<int> dp;
    for (int i = 0; i < N; i++) {
        int j = lower_bound(dp.begin(), dp.end(), A[i]) - dp.begin();
        if (j == dp.size()) {
            dp.push_back(A[i]);
        } else {
            dp[j] = A[i];
        }
    }

    cout << dp.size() << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N);

    return 0;
}