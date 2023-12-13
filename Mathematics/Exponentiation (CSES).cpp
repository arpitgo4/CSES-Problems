// Exponentiation (CSES)
 
#include <iostream>
 
using namespace std;
using ll = long long;

// Time: O(log(pow))
// Space: O(log(pow))

const int MOD = 1e9 + 7;
 
void solve(int num, int pow) {
    int res = 1;
    while (pow > 0) {
        if (pow % 2 == 1) {
            res = (res * 1ll * num) % MOD;
            pow--;
        }

        num = (num * 1ll * num) % MOD;
        pow /= 2;
    }

    cout << res << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t, a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        solve(a, b);
    }
    
    return 0;
}