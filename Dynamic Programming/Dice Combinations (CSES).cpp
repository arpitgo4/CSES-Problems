// Dice Combinations (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N)
// Space: O(N)

const int MAX_NUM = 1e6 + 1; 
const int MOD = 1e9 + 7;
vector<int> dp(MAX_NUM, 0);

void solve(int N) {
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= N; i++)
        for (int j = 1; j <= 6 && i >= j; j++)
            dp[i] = (dp[i] + dp[i-j]) % MOD;

    cout << dp[N] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    solve(N);

    return 0;
}