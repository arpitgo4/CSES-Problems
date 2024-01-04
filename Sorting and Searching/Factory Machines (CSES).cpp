// Factory Machines (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;
 
// Time: O(Nlog(1e18)) ~ O(N * 60) ~ O(N)
// Space: O(1)

bool can_do(ll max_time, vector<ll>& machines, ll K) {
    ll counter = 0;
    for (ll time : machines) {
        counter += (max_time/time);

        if (counter >= K)
            return true;
    }

    return false;
}

void solve(vector<ll>& machines, int N, ll K) {
    ll l = 0, h = 1e18;
    while (l <= h) {
        ll m = (h-l)/2 + l;
        if (can_do(m, machines, K))
            h = m-1;
        else l = m+1;
    }

    cout << l;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N, K;
    cin >> N >> K;

    vector<ll> machines(N);
    for (int i = 0; i < N; i++)
        cin >> machines[i];

    solve(machines, N, K);
    
    return 0;
}