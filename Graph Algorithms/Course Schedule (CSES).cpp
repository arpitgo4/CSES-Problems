// Course Schedule (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(V + E)
// Space: O(V + E)

typedef pair<int,int> edge;

vector<vector<int>> G;
vector<int> vis, topo;

bool cycle_found = false;

void dfs(int u) {
    vis[u] = 1;
    for (int v : G[u]) {
        if (vis[v] == 0) {
            dfs(v);
        } else if (vis[v] == 1) {
            cycle_found = true;
        }
    }

    vis[u] = 2;
    topo.push_back(u);
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    G.assign(V+1, vector<int>());
    vis.assign(V+1, 0);
    for (auto& [ u, v] : edges)
        G[v].push_back(u);

    for (int u = 1; u <= V; u++)
        if (vis[u] == 0)
            dfs(u);

    if (cycle_found) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int u : topo)
            cout << u << " ";
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    int u, v;
    vector<edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(V, E, edges);

    return 0;
}