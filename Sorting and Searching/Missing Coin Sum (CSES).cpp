// Missing Coin Sum (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;

// Time: O(NlogN)
// Space: O(1)

void solve(vector<ll>& A, int N) {
    sort(A.begin(), A.end());

    if (A[0] != 1) {
        cout << 1;
        return;
    }

    ll min_sum = LLONG_MAX;
    for (int i = 1; i < N; i++) {
        if (A[i] > A[i-1]+1) {
            min_sum = A[i-1]+1;
            break;
        }
            
        A[i] += A[i-1];
    }

    if (min_sum == LLONG_MAX)
        min_sum = A[N-1] + 1;

    cout << min_sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N);

    return 0;
}