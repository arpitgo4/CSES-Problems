// Flight Routes Check (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
// Strongly-Connected Components
// Time: O(V + E)
// Space: O(V + E)

vector<vector<int>> G;
vector<int> low_link, vis, s_time;
vector<int> scc, on_stack;
stack<int> st;

int timer = 0;

// vis[v] == 2 (cross-edge or forward edge)
void dfs(int u) {
    vis[u] = 1;
    s_time[u] = low_link[u] = ++timer;
    st.push(u);
    on_stack[u] = true;

    for (int v : G[u]) {
        if (vis[v] == 0) {                                  // tree-edge
            dfs(v);
            low_link[u] = min(low_link[u], low_link[v]);
        } else if (on_stack[v])                             // back-edge
            low_link[u] = min(low_link[u], s_time[v]);
    }

    if (low_link[u] == s_time[u]) {
        scc.push_back(u);

        int v;
        do {
            v = st.top();
            st.pop();
            on_stack[v] = false;
        } while (v != u);
    }

    vis[u] = 2;
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    G.assign(V+1, vector<int>());
    low_link.assign(V+1, -1);
    s_time.assign(V+1, -1);
    vis.assign(V+1, 0);
    on_stack.assign(V+1, false);
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (vis[u] == 0)
            dfs(u);

    if (scc.size() == 1)
        cout << "YES";
    else {
        cout << "NO" << endl;
        int u = scc[0];
        int v = scc[1];
        for (int x : G[u])
            if (x == v) {
                cout << scc[1] << " " << scc[0];
                return;
            }

        cout << scc[0] << " " << scc[1];
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E;
    cin >> V >> E;

    int u, v;
    vector<pair<int,int>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(V, E, edges);
    
    return 0;
}