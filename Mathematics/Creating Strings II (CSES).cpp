// Creating Strings II (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;

// Time: O(Nlog(MOD)) ~ O(N)
// Space: O(N)

const ll MOD = 1e9 + 7;
const ll MAX_N = 1e6 + 1;

vector<ll> factorial_cache(MAX_N, -1);
vector<ll> inverse_factorial_cache(MAX_N, -1);
vector<ll> frequency(26, 0);
 
ll factorial(ll x) {
    if (x == 0)
        return 1;
    if (factorial_cache[x] != -1)
        return factorial_cache[x];
    return factorial_cache[x] = (x * factorial(x-1)) % MOD;
}

ll inverse_factorial(ll x) {
    if (inverse_factorial_cache[x] != -1)
        return inverse_factorial_cache[x];

    ll x_fact = factorial(x);
    ll res = 1, pow = MOD-2;
    while (pow > 0) {
        if (pow % 2 == 1)
            res = (res * x_fact) % MOD;
        x_fact = (x_fact * x_fact) % MOD;
        pow >>= 1;
    }

    return inverse_factorial_cache[x] = res;
}

void solve(string& S) {
    int N = S.length();
    for (char c : S)
        frequency[c - 'a']++;

    ll count = factorial(N);
    for (int a : frequency)
        count = (count * inverse_factorial(a)) % MOD;

    cout << count;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);   
    
    return 0;
}