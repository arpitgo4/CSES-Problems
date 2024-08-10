// Reading Books (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

// Time: O(N + Nlog1e18) ~ O(N)
// Space: O(N)

// 2 3 8
// partition diff = 8-(2+3) = 3
// T1 = 5, 3 (waiting), 8 = 16
// T2 = 8, 5 = 13
// total = max(T1, T2) = 16

// 4
// 2 3 5 8
// T1 = 10, 8 = 18
// T2 = 8 (2), 8 = 16
// total time taken = max(T1, T2) = 18

vector<ll> prefix_sum;

bool can_read(ll time_given, vector<ll>& T, int N) {
    ll min_diff = INT_MAX, max_sum = INT_MIN;
    for (int i = 0; i < N; i++) {
        ll left_sum = prefix_sum[i+1] - prefix_sum[0];
        ll right_sum = prefix_sum[N] - prefix_sum[i+1];
        ll diff = abs(right_sum-left_sum);
        if (diff < min_diff)
            min_diff = diff;
    }

    int time_required = min_diff + prefix_sum[N];

    return time_required <= time_given;
}

void solve(vector<ll>& T, int N) {
    sort(T.begin(), T.end());

    prefix_sum.assign(N+1, 0);
    for (int i = 1; i < N+1; i++)
        prefix_sum[i] = prefix_sum[i-1] + T[i-1];

    ll l = 1, h = 1e18;
    while (l <= h) {
        ll m = (h-l)/2 + l;
        if (can_read(m, T, N))
            h = m-1;
        else l = m+1;
    }

    cout << l;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<ll> T(N);
    for (int i = 0; i < N; i++)
        cin >> T[i];

    solve(T, N);
    
    return 0;
}