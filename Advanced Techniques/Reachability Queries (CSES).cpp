// Reachability Queries (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
#include <stack>
#include <bitset>
 
using namespace std;
 
// Time: O(V^2)
// Space: O(V + E)
 
/**
 * Can't even build Adjacency Matrix for graph with > 1e5 vertices
 * That would require ~ GM memory and limit for this problem is 512 MB
 * 
 * Use Strongly Connected Components to create a DAG (Condensed Graph). Time: O(V + E)
 * Use DP on above condensed graph to calculate reachability for all vertices. Time: O((V + E) * V)
*/
 
typedef pair<int,int> edge;
 
const int MAX_V = 5e4;
vector<bitset<MAX_V+1>> dp;

vector<vector<int>> G, G_scc;
vector<int> low_link, s_time, vis, P;
vector<bool> on_stack;
stack<int> st;

int timer = 0;

bool reachable(int u, int v) {
    return dp[P[u]].test(P[v]);
}

void dfs2(int u) {
    vis[u] = 1;

    dp[u].set(u);
    for (int v : G_scc[u]) {
        if (vis[v] == 0)
            dfs2(v);

        dp[u] |= dp[v];
    }

    vis[u] = 2;
}

void dfs(int u) {
    s_time[u] = timer++;
    low_link[u] = s_time[u];
    st.push(u);
    on_stack[u] = true;
    vis[u] = 1;

    for (int v : G[u]) {
        if (vis[v] == 0) {
            dfs(v);
            low_link[u] = min(low_link[u], low_link[v]);
        } else if (on_stack[v])
            low_link[u] = min(low_link[u], s_time[v]);
    }

    if (s_time[u] == low_link[u]) {
        int v;
        do {
            v = st.top();
            st.pop();
            on_stack[v] = false;

            P[v] = u;
        } while(v != u);
    }
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    G_scc.assign(V+1, vector<int>());
    vis.assign(V+1, 0);
    on_stack.assign(V+1, false);
    low_link.assign(V+1, -1);
    s_time.assign(V+1, -1);
    P.assign(V+1, -1);
    dp.assign(V+1, bitset<MAX_V+1>(0));
    for (int u = 1; u <= V; u++)
        P[u] = u;

    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (vis[u] == 0)
            dfs(u);

    for (edge& e : edges) {
        int u = e.first, v = e.second;
        if (P[u] != P[v])
            G_scc[P[u]].push_back(P[v]);
    }

    vis.assign(V+1, 0);
    for (int u = 1; u <= V; u++)
        if (vis[P[u]] == 0)
            dfs2(P[u]);
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