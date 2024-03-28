// Reachability Queries (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
 
// Time: O(V^3)
// Space: O(1)
 
/**
 * Can't even build Adjacency Matrix for graph with > 1e5 vertices
 * That would require ~ GM memory and limit for this problem is 512 MB
*/

#define INF INT_MAX
 
typedef long long ll;
typedef pair<int,int> edge;
 
vector<vector<int>> G;

void floyd_warshall_apsp(int V) {
    for (int k = 1; k <= V; k++)
        for (int u = 1; u <= V; u++)
            for (int v = 1; v <= V; v++)
                if (G[u][k] != INF && G[k][v] != INF)
                    G[u][v] = min(G[u][v], G[u][k] + G[k][v]);
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<int>(V+1, INF));
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u][v] = 1;
    }

    for (int u = 1; u <= V; u++)
        G[u][u] = 1;

    floyd_warshall_apsp(V);
}

bool reachable(int u, int v) {
    cout << u << ", " << v << endl;
    return G[u][v] != INF;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E, Q;
    cin >> V >> E >> Q;

    int u, v;
    vector<edge> edges(E);
    for (int i =  0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, V, E);

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        cout << (reachable(u, v) ? "YES" : "NO") << endl;
    }
    
    return 0;
}