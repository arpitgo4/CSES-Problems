// Bracket Sequences I (CSES)
 
#include <iostream>
 
using namespace std;
using ll = long long;
 
// Catalan Numbers
// catalan(n) = 1/(1+n) * (bino_coff(2n, n))

// Time: O(N)
// Space: O(1)

const int MOD = 1e9 + 7;

int factorial(int x) {
    int curr = 1, prev = 1;         // factorial(0)
    for (int i = 2; i <= x; i++) {
        curr = (prev * 1ll * i) % MOD;
        prev = curr;
    }

    return curr;
}

int inverse(int x) {
    int res = 1, pow = MOD-2;
    while (pow > 0) {
        if (pow % 2 == 1)
            res = (res * 1ll * x) % MOD;
        x = (x * 1ll * x) % MOD;
        pow >>= 1;
    }

    return res;
}

int bino_coff(int N, int M) {
    return factorial(N) * 1ll * inverse(factorial(M)) % MOD * 1ll * inverse(factorial(N-M)) % MOD;
}

void solve(int N) {
    if (N % 2 == 1) {
        cout << 0;
        return;
    }

    N /= 2;
    int catalan = bino_coff(2*N, N) * 1ll * inverse(1 + N) % MOD;
    cout << catalan;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    solve(N);
    
    return 0;
}