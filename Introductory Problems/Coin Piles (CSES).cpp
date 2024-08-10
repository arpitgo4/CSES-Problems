// Coin Piles (CSES)
 
#include <iostream>
#include <cmath>
 
using namespace std;
 
// Time: O(1)
// Space: O(1)

/**
 * We can remove minimum (3,3) ((2,1),(1,2)) coins from both piles in 2 moves
 * We can remove maximum (4,2) ((2,1),(2,1)) coins from either of the piles
 * 
 * ((2,1)(2,1))
 * ((2,1)(1,2))
 * 
 * pile 1: 2, 2, 2, ....
 * pile 2: 1, 1, 1, ....
 * 
 * pile 1: 2, 1, 2, 1 ....
 * pile 2: 1, 2, 1, 2 ....
 * 
 * pile 1: #2 == pile 2: #1
 * 
 * 4 4
 * 2 3  (2, 1)
 * 1 2  (1, 2)
 * 0 0
 * 
 * 3 3
 * 1 2  (2, 1)
 * 0 0 
 * 
 * 2 2  [X]
 * 0 1  (2, 1)
 * 
 * 1 1  [X]
 * 0 1  (1, 2)
 * 
 * x = 3
 * 2x + 1x = 6 + 3
 * 3x = (a + b)
 * x = (a + b) / 3
 * 6 + 3 = 9
 * 
 * total moves = x
 * total coins moved = (2x + 1x)
 * condition,
 *     1. Need to make a move on both piles i.e. both piles should be not empty till x moves
 * 
 * min(a,b) * 2 >= max(a,b)
 * min(a,b) >= max(a,b)/2
 * 
 * max(a,b)/1 => max moves available, maybe not possible
 * max(a,b)/2 => max moves possible w.r.t to smaller (other) pile
 */

typedef long long ll;

void solve(ll a, ll b) {
    ll sum = a + b;
    if (sum % 3 == 0 && max<ll>(a,b) <= (2 * min<ll>(a,b)))
        cout << "YES" << endl;
    else cout << "NO" << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        ll a, b;
        cin >> a >> b;
        
        solve(a, b);
    }
    
    return 0;
}