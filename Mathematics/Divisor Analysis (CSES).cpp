// Divisor Analysis (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
typedef long long ll;
 
const ll MOD = 1e9 + 7;

// Time: O(N * log(max(power of prime)))
// Space: O(1)

ll binary_exponentiation(ll x, ll p, ll mod) {
    ll res = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            res = res * x % mod;
            p--;
        }

        x = x * x % mod;
        p /= 2;
    }

    return res;
}

ll modular_inverse(ll x) {
    return binary_exponentiation(x, MOD-2, MOD);
}

// Time: O(N + log(pow)), Space: O(1)
ll product_all_factors(vector<pair<ll,ll>>& factors, ll N, ll tau) {
    ll res = 1;
    for (pair<ll,ll>& p : factors) {
        ll pr = p.first, pow = p.second;
        ll tau_power = binary_exponentiation(pow, tau * modular_inverse(2) % MOD, MOD-1);
        res = res * binary_exponentiation(pr, tau_power, MOD);
    }

    return res;
}

// Time: O(Nlog(pow)), Space: O(1)
ll sum_all_factors(vector<pair<ll,ll>>& factors, ll N) {
    ll res = 1;
    for (pair<ll,ll>& p : factors) {
        ll x = p.first, pow = p.second;
        ll y = (binary_exponentiation(x, pow+1, MOD) - 1) * modular_inverse(x-1) % MOD;
        res = res * y % MOD;
    }

    return res;
}

// Time: O(N), Space: O(1)
ll count_all_factors(vector<pair<ll,ll>>& factors, ll N) {
    ll count = 1;
    for (pair<ll,ll>& p : factors) {
        ll pow = p.second;
        count = (count * (pow + 1)) % MOD;
    }

    return count;
}

void solve(vector<pair<ll,ll>>& factors, ll N) {
    ll tau = count_all_factors(factors, N);
    ll sigma = sum_all_factors(factors, N);
    ll myu = product_all_factors(factors, N, tau);

    cout << tau << " " << sigma << " " << myu;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N;
    cin >> N;

    ll p, pow;
    vector<pair<ll,ll>> factors(N);
    for (int i = 0; i < N; i++) {
        cin >> p >> pow;
        factors[i] = { p, pow };
    }

    solve(factors, N);
    
    return 0;
}