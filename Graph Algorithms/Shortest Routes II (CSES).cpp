// Shortest Routes II (CSES)

#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using ll = long long int;

// Floyd-Warshall All Pairs Shortest Path
// Time: O(V^3)
// Space: O(V^2)

void solve(vector<vector<ll>>& G, int V) {
    for (int u = 1; u <= V; u++)
        for (int v = 1; v <= V; v++)
            for (int k = 1; k <= V; k++) {
                if (G[u][k] != LLONG_MAX && G[k][v] != LLONG_MAX) {
                    G[v][u] = G[u][v] = min({ G[v][u], G[u][v], G[u][k] + G[k][v] });
                }
            }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E, Q;
    cin >> V >> E >> Q;

    vector<vector<ll>> G(V+1, vector<ll>(V+1, LLONG_MAX));
    int u, v; ll w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        G[u][v] = w;
        G[v][u] = w;
    }

    solve(G, V);

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        if (G[u][v] == LLONG_MAX)
            cout << -1 << endl;
        else cout << G[u][v] << endl;
    }

    return 0;
}