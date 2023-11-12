// Stick Lengths (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;

// Time: O(NlogN)
// Space: O(1)

// TODO: IMPROVEMENT, can be done in best & average: O(N) time and worst case O(N^2) time with quick select to get target_length

ll calculate_cost(vector<ll>& A, int N, ll target_len) {
    ll cost = 0;
    for (int i = 0; i < N; i++)
        cost += abs(A[i] - target_len);

    return cost;
}

void solve(vector<ll>& A, int N) {
    sort(A.begin(), A.end());

    if (N % 2 == 1)
        cout << calculate_cost(A, N, A[N/2]);
    else 
        cout << min(calculate_cost(A, N, A[N/2-1]), calculate_cost(A, N, A[N/2]));
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