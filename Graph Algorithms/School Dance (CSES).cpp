// School Dance (CSES)
 
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
 
using namespace std;

// Unweighted Maximum Cardinality Bipartite Graph Matching (Unweighted MCBM)
// can use Edmond-Karp's Max-Flow algorithm

// Time: O(V * E^2)
// Space: O(E)
 
#define INF INT_MAX
 
typedef pair<int,int> edge;
typedef pair<int,int> state;

int BASE_V1, BASE_V2, SRC, SINK, V;

vector<vector<int>> G, C;
vector<int> vis, P;

int bfs(int V) {
    vis.assign(V+1, 0);
    P.assign(V+1, -1);

    queue<state> q({{ SRC, INF }});
    vis[SRC] = 1;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int u = p.first, flow = p.second;
        if (u == SINK)
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

int maximum_flow(int V) {
    int flow = 0, max_flow = 0;
    while ((flow = bfs(V)) > 0) {
        max_flow += flow;

        int curr = SINK;
        while (curr != SRC) {
            int prev = P[curr];
            C[prev][curr] -= flow;
            C[curr][prev] += flow;
            curr = prev;
        }
    }

    return max_flow;
}

void build_graph(vector<edge>& edges, int V1, int V2) {
    SRC = 1;
    BASE_V1 = 2;
    BASE_V2 = BASE_V1 + V1;
    SINK = V1 + V2 + SRC + 1;
    V = SINK;

    G.assign(V+1, vector<int>());
    C.assign(V+1, vector<int>(V+1, 0));

    for (int i = 0; i < V1; i++) {
        int u = SRC, v = BASE_V1 + i;
        G[u].push_back(v);
        G[v].push_back(u);
        C[u][v] = 1;
    }

    for (edge& e : edges) {
        int u = e.first + BASE_V1 - 1, v = e.second + BASE_V2 - 1;
        G[u].push_back(v);
        G[v].push_back(u);
        C[u][v] = 1;
    }

    for (int i = 0; i < V2; i++) {
        int u = BASE_V2 + i, v = SINK; 
        G[u].push_back(v);
        G[v].push_back(u);
        C[u][v] = 1;
    }
}

void solve(vector<edge>& edges, int V1, int V2) {
    build_graph(edges, V1, V2);

    int count = maximum_flow(V);
    cout << count << endl;

    for (edge& e : edges) {
        int u = e.first + BASE_V1 - 1, v = e.second + BASE_V2 - 1;
        if (C[u][v] == 0)
            cout << (u-BASE_V1+1) << " " << (v-BASE_V2+1) << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V1, V2, K;
    cin >> V1 >> V2 >> K;

    int u, v;
    vector<edge> edges(K);
    for (int i = 0; i < K; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, V1, V2);
    
    return 0;
}