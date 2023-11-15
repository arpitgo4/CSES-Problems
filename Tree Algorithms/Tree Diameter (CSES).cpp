// Tree Diameter (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Time: O(N)
// Space: O(N)

vector<vector<int>> T;
vector<int> VIS;
int diameter = 0;

int dfs(int u) {
    VIS[u] = 1;

    vector<int> dists;
    for (int v : T[u])
        if (VIS[v] == 0)
            dists.push_back(1 + dfs(v));

    priority_queue<int> pq(dists.begin(), dists.end());
    
    if (pq.empty())
        return 0;

    int a = pq.top();
    pq.pop();

    int b = 0;
    if (!pq.empty())
        b = pq.top();

    diameter = max({ diameter, a + b });
    return a;
}

void solve(vector<pair<int,int>>& E, int V) {
    T.assign(V+1, vector<int>());
    VIS.assign(V+1, 0);

    for (pair<int,int>& p : E) {
        int u = p.first, v = p.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    int max_dist = dfs(1);

    cout << max(max_dist, diameter);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<pair<int,int>> E(N-1);
    int a, b;
    for (int i = 0; i < N-1; i++) {
        cin >> a >> b;
        E[i] = { a, b };
    }

    solve(E, N);

    return 0;
}