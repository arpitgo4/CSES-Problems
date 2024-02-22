// High Score (CSES)

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <tuple>
#include <bitset>

using namespace std;

// Time: O(VE + (V + E)) ~ O(VE)
// Space: O(V)

/**
 * 1. Bellman-ford will provide all the nodes involved in +ve cycles that are reachable 
 * from source (src_mask)
 * 2. DFS from destination vertex on transposed graph gives us the reachability vertex
 * set from destination (dest_mask)
 * 
 * If there is an intersection between src_mask & dest_mask, that means, destination vertex
 * is reachable from a +ve cycle that is also reachable from source. We can have infinitely
 * large score, hence, result is -1
 * Otherwise, traverse the shortest path tree from destination vertex to source vertex and
 * return the path weight (i.e. max score)
*/

#define INF LLONG_MAX

typedef long long ll;
typedef tuple<int,int,ll> edge;
typedef pair<int,ll> graph_edge;

const int MAX_V = 2500;

vector<vector<graph_edge>> GT;
vector<ll> dist;
vector<graph_edge> P;                               // shortest-path tree
bitset<MAX_V+1> src_mask, dest_mask;
vector<int> vis;

bool bellman_ford_sssp(int src, int V, vector<edge>& edges) {
    dist[src] = 0;

    int u, v; ll w;
    for (int i = 0; i < V-1; i++) {
        for (edge& e : edges) {
            tie(u,v,w) = e;
            w = -w;
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                P[v] = { u, -w };
            }
        }
    }

    bool any = false;
    for (edge& e : edges) {
        tie(u,v,w) = e;
        w = -w;
        if (dist[u] != INF && dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            P[v] = { u, -w };
            src_mask.set(v);
            any = true;
        }
    }

    return any;
}

void dfs(int u) {
    vis[u] = 1;

    for (graph_edge& e : GT[u]) {
        int v = e.first;
        if (vis[v] == 0)
            dfs(v);

        dest_mask.set(v);
    }

    vis[u] = 2;
}

void solve(vector<edge>& edges, int E, int V) {
    GT.assign(V+1, vector<graph_edge>());
    dist.assign(V+1, INF);
    P.assign(V+1, { -1, INF });
    vis.assign(V+1, 0);
 
    int u, v; ll w;
    for (edge& e : edges) {
        tie(u, v, w) = e;
        GT[v].push_back({ u, w });
    }

    bellman_ford_sssp(1, V, edges);
    dfs(V);

    if ((src_mask & dest_mask) != 0) {
        cout << -1 << endl;
        return;
    }

    ll max_score = 0;
    graph_edge& curr = P[V];
    while (curr.first != -1) {
        max_score += curr.second;
        curr = P[curr.first];
    }

    cout << max_score << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<edge> edges(E);
    int u, v; ll w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(edges, E, V);

    return 0;
}