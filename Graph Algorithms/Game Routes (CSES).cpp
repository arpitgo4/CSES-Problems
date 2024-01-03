// Game Routes (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(V + E)
// Space: O(V + E)

/**
 * No need to do topological sort first. As problem states that the game routes is a DAG and we already have the
 * starting point Level-1. Dynamic Programming is enough to count number of possible routes in the given DAG.
*/

const int MOD = 1e9 + 7;
vector<vector<int>> G;
vector<int> cache;

int dfs(int u, int dest) {
    if (u == dest)
        return 1;
    if (cache[u] != -1)
        return cache[u];

    int count = 0;
    for (int v : G[u])
        count = (count + dfs(v, dest)) % MOD;

    return cache[u] = count;
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    G.assign(V+1, vector<int>());
    cache.assign(V+1, -1);

    for (pair<int,int>& p : edges) {
        int u = p.first, v = p.second;
        G[u].push_back(v);
    }

    int count = dfs(1, V);
    cout << count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<pair<int,int>> edges(E);
    int u, v;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(V, E, edges);

    return 0;
}