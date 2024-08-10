// Distinct Routes (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
 
using namespace std;
 
/**
 * Node-Disjoint Paths
 * Set of paths in which any node is part of at-most one path
 * 
 * Can be solved as maximum-flow problem, by modelling each node in the 
 * graph two identical nodes with first-one having all the incoming edges
 * and second-one with all outgoing edges. First and second node will have
 * a single edge between them with capacity of 1.
*/

// Time: O(V * E^2)
// Space: O(E)

#define INF INT_MAX
 
typedef pair<int,int> edge;
typedef pair<int,int> state;
 
vector<vector<vector<int>>> G, C;
vector<int> vis, P;

// G[u][0] => first node
// G[u][1] => second node
// C[u][1] = 1;                     // in-capacity from [u][0] => [u][1]

int bfs(int src, int sink, int V) {
    vis.assign(V+1, 0);
    P.assign(V+1, -1);

    queue<state> q({{ src, INF }});
    vis[src] = 1;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int u = p.first, flow = p.second;
        if (u == sink)
            return flow;

        if (C[u][0][u] > 0) {
            for (int v : G[u][1]) {
                if (vis[v] == 0 && C[u][1][v] > 0) {
                    int new_flow = min(flow, C[u][1][v]);
                    P[v] = u;
                    vis[v] = 1;
                    q.push({ v, new_flow });
                }
            }    
        }
    }

    return 0;
}

int maximum_flow(int src, int sink, int V) {
    int flow = 0, max_flow = 0;
    while ((flow = bfs(src, sink, V)) > 0) {
        max_flow += flow;

        int curr = sink;
        while (curr != src) {
            int prev = P[curr];
            C[prev][1][curr] -= flow;
            C[curr][1][prev] += flow;
            C[prev][0][prev] -= flow;
            curr = prev;
        }
    }

    return max_flow;
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<vector<int>>(2, vector<int>()));
    C.assign(V+1, vector<vector<int>>(2, vector<int>(V+1, 0)));

    /**
     * Rest of the algorithm is mostly standard with some tweaking here
     * and there
     * 
     * TODO: Check the graph modelling logic
    */

    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u][1].push_back(v);
        G[v][0].push_back(u);
        C[u][1][v] = 1;
    }

    for (int u = 1; u <= V; u++) {
        G[u][1].push_back(u);
        G[u][0].push_back(u);
        C[u][0][u] = 1;
    }

    int max_flow = maximum_flow(1, V, V);
    cout << max_flow << endl;

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