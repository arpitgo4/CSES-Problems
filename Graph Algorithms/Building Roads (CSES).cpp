// Building Roads (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

// Time: O(V + E)
// Space: O(V + E)

vector<vector<int>> G;
vector<int> VIS;

void dfs(vector<vector<int>>& G, int u) {
    VIS[u] = 1;

    for (int v : G[u])
        if (VIS[v] == 0)
            dfs(G, v);
}

void solve(int V, int E, vector<vector<int>>& G) {
    VIS.assign(V+1, 0);
    
    vector<int> reps;
    for (int u = 1; u <= V; u++)
        if (VIS[u] == 0) {
            reps.push_back(u);
            dfs(G, u);
        }

    cout << reps.size()-1 << endl;
    if (reps.size() < 2)
        return;

    int N = reps.size();
    int u = reps[0];
    for (int i = 1; i < N; i++) {
        int v = reps[i];
        cout << u << " " << v << endl;
        u = v;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<vector<int>> G(V+1, vector<int>());
    int u, v;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    solve(V, E, G);

    return 0;
}