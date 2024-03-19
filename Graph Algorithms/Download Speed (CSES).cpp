// Download Speed (CSES)
 
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>
 
using namespace std;
 
// Time: O(V * E^2)
// Space: O(E)
 
#define INF LLONG_MAX
 
typedef long long ll;
typedef tuple<int,int,ll> edge;

vector<vector<int>> G;
vector<vector<ll>> C;
vector<int> P, vis;                                     // shortest-path tree
 
ll bfs(int src, int sink, int V) {
    vis.assign(V+1, 0);
    P.assign(V+1, -1);

    queue<pair<int,ll>> q({{ src, INF }});
    vis[src] = 1;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int u = p.first; 
        ll flow = p.second;
        if (u == sink)
            return flow;

        for (int v : G[u]) {
            if (vis[v] == 0 && C[u][v] > 0) {
                ll new_flow = min(flow, C[u][v]);
                P[v] = u;
                vis[v] = 1;
                q.push({ v, new_flow });
            }
        }
    }

    return 0;
}

ll maximum_flow(int src, int sink, int V) {
    ll max_flow = 0, flow = 0;
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
    C.assign(V+1, vector<ll>(V+1, 0));

    int u, v; ll c;
    for (edge& e : edges) {
        tie(u, v, c) = e;
        G[u].push_back(v);
        G[v].push_back(u);
        C[u][v] += c;
    }

    ll max_flow = maximum_flow(1, V, V);
    cout << max_flow << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E;
    cin >> V >> E;

    int u, v; ll c;
    vector<edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> c;
        edges[i] = { u, v, c };
    }

    solve(edges, V, E);
    
    return 0;
}