// Binomial Coefficients (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;

// Time: O(MAX_N + MAX_N * log(MOD)) ~ O(1)     // MAX_N => for factorials + MAX_N*log(MOD) => for inverses
// Space: O(MAX_N) ~ O(1)

const ll MOD = 1e9 + 7;
const ll MAX_N = 1e6;

vector<ll> factorial_cache(MAX_N + 1, -1);
vector<ll> inverse_cache(MAX_N + 1, -1);

ll factorial(ll x) {
    if (x == 0)
        return 1;
    if (factorial_cache[x] != -1)
        return factorial_cache[x];
    return factorial_cache[x] = (x * factorial(x-1)) % MOD;
}

// wrapped factorial in inverse function, this way input value for x will stay <= 1e6
// and function's input can be used as the cache key
ll inverse_factorial(ll x) {
    if (inverse_cache[x] != -1)
        return inverse_cache[x];

    ll x_fact = factorial(x);
    ll res = 1, pow = MOD-2;
    while(pow > 0){
        if(pow % 2 == 1)
            res = (res * x_fact) % MOD;
        x_fact = (x_fact * x_fact) % MOD;
        pow >>= 1;
    }

    return inverse_cache[x] = res;
}

ll bin_coff(ll a, ll b) {
    return factorial(a) * inverse_factorial(b) % MOD * inverse_factorial(a-b) % MOD;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    ll a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        cout << bin_coff(a, b) << endl;
    }
    
    return 0;
}