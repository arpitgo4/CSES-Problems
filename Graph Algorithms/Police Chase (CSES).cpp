// Police Chase (CSES)
 
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
 
using namespace std;
 
// Time: O(V * E^2)
// Space: O(E)

#define INF INT_MAX
 
typedef long long ll;
typedef pair<int,int> edge;
 
vector<vector<int>> G, C;
vector<int> vis, P;

void dfs(int u) {
    vis[u] = 1;

    for (int v : G[u]) {
        if (vis[v] == 0 && C[u][v] > 0)
            dfs(v);
    }

    vis[u] = 2;
}

int bfs(int src, int sink, int V) {
    P.assign(V+1, -1);
    vis.assign(V+1, 0);

    queue<pair<int,int>> q({{ src, INF }});
    vis[src] = 1;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int u = p.first, flow = p.second;
        if (u == sink)
            return flow;

        for (int v : G[u]) {
            if (vis[v] == 0 && C[u][v] > 0) {
                vis[v] = 1;
                P[v] = u;
                q.push({ v, min(flow, C[u][v]) });
            }
        }
    }

    return 0;
}

int maximum_flow(int src, int sink, int V) {
    int max_flow = 0, flow = 0;
    while ((flow = bfs(src, sink, V)) > 0) {
        max_flow += flow;

        int curr = sink;
        while (curr != src) {
            int prev = P[curr];
            C[prev][curr] -= flow;
            C[curr][prev] += flow;
            curr = prev;
        }
    }

    return max_flow;
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    C.assign(V+1, vector<int>(V+1, 0));
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
        G[v].push_back(u);
        C[u][v] = C[v][u] = 1;
    }

    int min_cut = maximum_flow(1, V, V);                    // max_flow = min_cut
    cout << min_cut << endl;

    vis.assign(V+1, 0);
    dfs(1);

    for (int u = 1; u <= V; u++) {
        if (vis[u] == 0)
            continue;

        for (int v : G[u]) {
            if (vis[v] == 0)
                cout << u << " " << v << endl;
        }
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