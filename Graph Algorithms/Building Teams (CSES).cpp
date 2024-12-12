// Building Teams (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;

// Time: O(V + E)
// Space: O(V + E)

typedef pair<int,int> edge;

vector<vector<int>> G;
vector<int> vis, color;

bool is_bipartite_graph = true;

void dfs(int u, int c) {
    vis[u] = 1;
    color[u] = c;

    for (int v : G[u]) {
        if (vis[v] == 0) {
            dfs(v, (c+1) % 2);
        } else {
            if (color[v] == c)
                is_bipartite_graph = false;
        }
    }

    vis[u] = 2;
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    vis.assign(V+1, 0);
    color.assign(V+1, -1);
    for (auto& [u, v] : edges) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int u = 1; u <= V; u++) {
        if (vis[u] == 0) {
            dfs(u, 0);
        }
    }

    if (!is_bipartite_graph) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int u = 1; u <= V; u++)
            cout << (color[u] + 1) << " ";
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

    solve(edges, V, E);
    
    return 0;
}