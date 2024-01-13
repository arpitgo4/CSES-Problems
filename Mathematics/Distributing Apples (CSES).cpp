// Distributing Apples (CSES)
 
#include <iostream>
 
using namespace std;
using ll = long long;
 
// Time: O(N * logMOD) ~ O(N)
// Space: O(1)

const ll MAX_N = 1e7;
const ll MOD = 1e9 + 7;

// TODO: can pre-compute all values faster with DP
// recursive impl. is prone to stack-overflow with x = 1e6 
// iterative impl is efficient enough for a single time use only
// because it starts calculation for x! from start if invoked multiple times
ll factorial(ll x) {
    ll prev = 1, curr = 1;            // factorial(0)
    for (int i = 1; i <= x; i++) {
        curr = (prev * i) % MOD;
        prev = curr;
    }
    
    return curr;
}

ll inverse_factorial(ll x) {
    ll x_fact = factorial(x);
    ll res = 1, pow = MOD-2;
    while (pow > 0) {
        if (pow % 2 == 1)
            res = (res * x_fact) % MOD;
        x_fact = (x_fact * x_fact) % MOD;
        pow >>= 1;
    }

    return res;
}

ll bin_coff(ll N, ll M) {
    return factorial(N) * inverse_factorial(M) % MOD * inverse_factorial(N-M) % MOD;
}

void solve(ll N, ll M) {
    // considering the problem to be creating a string with "o" & "->"
    // "o" denotes ball and "->" moving on to next box
    // string will have `m` "o"
    // and, `n-1` "->"
    // string's length will be `n+1`
    // #ways = C(m+n-1, m)
    // total spots to place chars: m+n-1
    // number of spots to choose for `m` "o": m

    cout << bin_coff(M+N-1, M);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N, M;
    cin >> N >> M;

    solve(N, M);
    
    return 0;
}