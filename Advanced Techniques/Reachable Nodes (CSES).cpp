// Reachable Nodes (CSES)
 
#include <iostream>
#include <vector>
#include <bitset>
 
using namespace std;
 
// Time: O(V * (V + E))
// Space: O(V^2)

const int MAX_V = 5e4;

vector<vector<int>> G;
vector<bitset<MAX_V+1>> dp;              // 5KB per mask, #masks = V, 25KB masks

void dfs(int u) {
    dp[u].set(u);
    for (int v : G[u]) {
        if (dp[v] == 0)
            dfs(v);

        dp[u] |= dp[v];
    }
}

void solve(vector<pair<int,int>>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    dp.assign(V+1, bitset<MAX_V+1>());
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (dp[u] == 0)
            dfs(u);

    for (int u = 1; u <= V; u++)
        cout << dp[u].count() << " ";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E;
    cin >> V >> E;

    int u, v;
    vector<pair<int,int>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, V, E);
    
    return 0;
}