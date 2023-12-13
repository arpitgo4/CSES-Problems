// Exponentiation II (CSES)
 
#include <iostream>
 
using namespace std;
using ll = long long;

// Time: O(log(b^c))
// Space: O(log(b^c))

const int MOD = 1e9 + 7;

int pow(int num, int pow, int mod) {
    int res = 1;
    while (pow > 0) {
        if (pow % 2 == 1) {
            res = (res * 1ll * num) % mod;
            pow--;
        }

        num = (num * 1ll * num) % mod;
        pow /= 2;
    }

    return res;
}


void solve(int a, int b, int c) {
    cout << pow(a, pow(b, c, MOD-1), MOD) << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t, a, b, c;
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        solve(a, b, c);    
    }
    
    return 0;
}