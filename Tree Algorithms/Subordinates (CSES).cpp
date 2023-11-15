// Subordinates (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

// Time: O(N)
// Space: O(N)

vector<vector<int>> T;
vector<ll> S;
vector<int> VIS;

int dfs(int u) {
    VIS[u] = 1;

    for (int v : T[u])
        if (VIS[v] == 0)
            S[u] += 1 + dfs(v);

    return S[u];
}

void solve(vector<int>& A, int N) {
    T.assign(N+1, vector<int>());
    S.assign(N+1, 0);
    VIS.assign(N+1, 0);

    for (int u = 2; u <= N; u++) {
        int v = A[u];
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1);

    for (int i = 1; i <= N; i++)
        cout << S[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> A(N+1);
    A[1] = -1;
    for (int i = 2; i <= N; i++)
        cin >> A[i];

    solve(A, N);

    return 0;
}