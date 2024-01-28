// Building Teams (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;

// Time: O(V + E)
// Space: O(V + E)
 
vector<vector<int>> G;
vector<int> team;
bool is_bipartite = true;

void dfs(int u, int color) {
    team[u] = color;

    for (int v : G[u]) {
        if (team[v] == team[u])
            is_bipartite = false;
        if (team[v] == -1)
            dfs(v, (color + 1) % 2);
    }
}

void solve(vector<pair<int,int>>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    team.assign(V+1, -1);
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int u = 1; u <= V; u++)
        if (team[u] == -1)
            dfs(u, 0);

    if (!is_bipartite)
        cout << "IMPOSSIBLE";
    else {
        for (int u = 1; u <= V; u++)
            cout << (team[u]+1) << " ";
    }
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