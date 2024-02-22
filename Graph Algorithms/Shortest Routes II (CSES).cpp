// Shortest Routes II (CSES)

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <climits>

using namespace std;

// Time: O(V^3)
// Space: O(1)

#define INF LLONG_MAX

typedef long long ll;
typedef tuple<int,int,ll> edge;

vector<vector<ll>> G;

void floyd_warshall_apsp(int V) {
    for (int u = 1; u <= V; u++)                // distance to self is zero
        G[u][u] = 0;

    for (int k = 1; k <= V; k++)
        for (int u = 1; u <= V; u++)
            for (int v = 1; v <= V; v++) {
                if (G[u][k] != INF && G[k][v] != INF)
                    G[v][u] = G[u][v] = min(G[u][v], G[u][k] + G[k][v]);
            }
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<ll>(V+1, INF));

    int u, v; ll w;
    for (edge& e : edges) {
        tie(u, v, w) = e;
        G[v][u] = G[u][v] = min({ G[v][u], G[u][v], w });      // if there are multiple edges between a pair of vertex
    }

    floyd_warshall_apsp(V);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E, Q;
    cin >> V >> E >> Q;

    int u, v; ll w;
    vector<edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(edges, V, E);

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        cout << (G[u][v] == INF ? -1 : G[u][v]) << endl; 
    }

    return 0;
}