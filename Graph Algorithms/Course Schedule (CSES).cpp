// Course Schedule (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(V + E)
// Space: O(V + E)

vector<vector<int>> G;
vector<int> VIS;
vector<int> topoSort;
bool cycle_found = false;

void dfs(vector<vector<int>>& G, int u) {
    VIS[u] = 1;

    for (int v : G[u]) {
        if (VIS[v] == 0)
            dfs(G, v);
        else if (VIS[v] == 1) {
            cycle_found = true;
            return;
        }
    }

    VIS[u] = 2;
    topoSort.push_back(u);
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    VIS.assign(V+1, 0);
    G.assign(V+1, vector<int>());
    for (pair<int,int>& edge : edges) {
        int u = edge.first, v = edge.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (VIS[u] == 0)
            dfs(G, u);

    if (cycle_found) {
        cout << "IMPOSSIBLE";
        return;
    }

    for (int u : topoSort)
        cout << u << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    int a, b;
    vector<pair<int,int>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> a >> b;
        edges[i] = { b, a };
    }

    solve(V, E, edges);

    return 0;
}