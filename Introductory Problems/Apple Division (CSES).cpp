// Apple Division (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;

// Time: O(2^N)
// Space: O(N)

ll dfs(int i, ll gp1, ll gp2, vector<ll>& A, int N) {
    if (i == N)
        return abs(gp1-gp2);
    
    ll a = dfs(i+1, gp1 + A[i], gp2, A, N);
    ll b = dfs(i+1, gp1, gp2 + A[i], A, N);

    return min(a, b);
}

void solve(vector<ll>& A, int N) {
    ll res = dfs(0, 0, 0, A, N);
    cout << res;
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