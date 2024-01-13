// Christmas Party (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;
 
// Derangements
// Time: O(N)
// Space: O(N)

const ll MAX_N = 1e6;
const ll MOD = 1e9 + 7;

vector<ll> dp(MAX_N + 1, -1);

// !n = count of derangements
// !n = (n-1) * (!(n-2) + !(n-1))       (recurrence relation)
// f(n) = (n-1) * (f(n-2) + f(n-1))     (top-down DP) (prone to stack-overflow for large n)
// dp(n) = (n-1) * (dp(n-2) + dp(n-1))  (bottom-up DP)
 
void solve(ll N) {
    dp[1] = 0;                          // !1
    dp[2] = 1;                          // !2
    for (int x = 3; x <= N; x++)
        dp[x] = (x-1) * ((dp[x-2] + dp[x-1]) % MOD) % MOD;

    cout << dp[N];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N;
    cin >> N;

    solve(N);
    
    return 0;
}