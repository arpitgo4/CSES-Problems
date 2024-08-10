// Two Sets (CSES)
 
#include <iostream>
#include <unordered_set>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)

typedef long long ll;
 
void solve(ll N) {
    ll total = (N * (N+1)) / 2;
    if (total % 2 == 1) {
        cout << "NO" << endl;
        return;
    }

    ll target = total / 2;
    ll sum = 0;
    unordered_set<ll> uSet;
    for (ll num = N; num > 0 && sum != target; num--) {
        if (sum + num <= target) {
            sum += num;
            uSet.insert(num);
        }
    }

    cout << "YES" << endl;
    cout << uSet.size() << endl;
    for (ll a : uSet)
        cout << a << " ";
    cout << endl;

    cout << (N-uSet.size()) << endl;
    for (ll i = 1; i <= N; i++) {
        if (uSet.find(i) == uSet.end())
            cout << i << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    solve(N);
    
    return 0;
}