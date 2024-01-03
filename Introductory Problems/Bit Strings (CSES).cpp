// Bit Strings (CSES)

#include <iostream>

using namespace std;
using ll = long long;

// Time: O(logN)
// Space: O(1)

const ll MOD = 1e9 + 7;

ll power(ll N, ll pow) {
    ll res = 1;
    while (pow > 0) {
        if (pow % 2 == 1)
            res = (res * N) % MOD;
        N = (N * N) % MOD;
        pow /= 2;
    }

    return res;
}

void solve(ll N) {
    cout << power(2, N);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N;
    cin >> N;

    solve(N);

    return 0;
}