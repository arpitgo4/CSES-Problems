// Coin Collector (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
typedef long long ll;
typedef pair<int,int> edge;
 
vector<vector<int>> G, G_scc;
vector<int> vis, s_time, low_link;
vector<int> scc_roots, P;
vector<bool> on_stack;
stack<int> st;

int timer = 0;

vector<ll> coins, dp;

ll dfs2(int u) {
    if (dp[u] != -1)
        return dp[u];

    ll max_coins = coins[u];
    for (int v : G_scc[u]) {
        max_coins = max(max_coins, coins[u] + dfs2(v));
    }

    return dp[u] = max_coins;
}

void dfs(int u) {
    s_time[u] = low_link[u] = timer++;
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
        scc_roots.push_back(u);

        int v;
        do {
            v = st.top();
            st.pop();
            on_stack[v] = false;
            P[v] = u;
        } while(v != u);
    }
}

void solve(vector<edge>& edges, int V, int E, vector<ll>& coins) {
    G.assign(V+1, vector<int>());
    G_scc.assign(V+1, vector<int>());
    vis.assign(V+1, 0);
    s_time.assign(V+1, -1);
    low_link.assign(V+1, -1);
    P.assign(V+1, -1);
    on_stack.assign(V+1, false);
    dp.assign(V+1, -1);

    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (vis[u] == 0)
            dfs(u);

    for (int u = 1; u <= V; u++) {
        if (P[u] != u)
            coins[P[u]] += coins[u];
    }

    for (edge& e : edges) {
        int u = e.first, v = e.second;
        if (P[u] != P[v]) {
            G_scc[P[u]].push_back(P[v]);                        // condensed graph
        }
    }

    ll max_coins = 0;
    for (int u = 1; u <= V; u++)
        max_coins = max(max_coins, dfs2(u));
    cout << max_coins << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E;
    cin >> V >> E;

    coins.assign(V+1, 0);
    for (int i = 1; i <= V; i++)
        cin >> coins[i];

    int u, v;
    vector<edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, V, E, coins);
    
    return 0;
}