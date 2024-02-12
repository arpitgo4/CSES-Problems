// Cycle Finding (CSES)
 
#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <algorithm>
 
using namespace std;

// Time: O(VE)
// Space: O(V)

#define INF LLONG_MAX

typedef long long ll;
typedef tuple<int,int,ll> edge;

vector<ll> dist;
vector<int> P;                                          // shortest-path (SP) tree

int bellman_ford_sssp(int src, int V, vector<edge>& edges) {
    int cycle_vertex = 0;
    int u, v; ll w;
    for (int i = 0; i < V && cycle_vertex != -1; i++) {                 // iterating V times instead of (V-1), to also check for presence of negative cycle
        cycle_vertex = -1;

        for (edge& e : edges) {
            tie(u,v,w) = e;
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                P[v] = u;             // Vth iteration, will form a cycle in the SP tree. Root of the tree will have parent as the lower-level child
                cycle_vertex = v;
            }
        }
    }

    return cycle_vertex;
}

void solve(vector<edge>& edges, int V, int E) {
    dist.assign(V+1, 0);                            // looking for shortest path simultaneously from all vertices. This helps in finding if there is neg-cycle reachable from any vertex, in case graph is disconnected. Otherwise, looking for a single source would have been fine!
    P.assign(V+1, -1);

    int cycle_vertex = bellman_ford_sssp(1, V, edges);
    if (cycle_vertex == -1) {
        cout << "NO" << endl;
        return;
    } else cout << "YES" << endl;

    for (int i = 0; i < V-1; i++)
        cycle_vertex = P[cycle_vertex];             // if cycle_vertex is a vertex that is reachable from -ve cycle, this loop will take us back into the -ve cycle!

    vector<int> cycle_path;
    int curr = cycle_vertex;
    do {
        cycle_path.push_back(curr);
        curr = P[curr];
    } while (curr != cycle_vertex);

    cycle_path.push_back(curr);
    reverse(cycle_path.begin(), cycle_path.end());

    for (int u : cycle_path)
        cout << u << " ";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E;
    cin >> V >> E;

    int u, v; ll w;
    vector<tuple<int,int,ll>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };    
    }

    solve(edges, V, E);   
    
    return 0;
}