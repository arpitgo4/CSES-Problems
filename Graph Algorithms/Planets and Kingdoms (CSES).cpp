// Planets and Kingdoms (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
 
using namespace std;
 
// Strongly-Connected Components
// Time: O(V + E)
// Space: O(V + E)
 
vector<vector<int>> G;
vector<int> low_link, vis, s_time, scc;
vector<bool> on_stack;
stack<int> st;

int scc_count = 0;
int timer = 0;

void dfs(int u) {
    vis[u] = 1;
    low_link[u] = s_time[u] = ++timer;       // timer, as monotonically-increasing id
    st.push(u);
    on_stack[u] = true;

    for (int v : G[u]) {
        if (vis[v] == 0) {                  // tree-edge
            dfs(v);
            low_link[u] = min(low_link[u], low_link[v]);
        } else if (on_stack[v]) {           // back-edge, if v is on_stack
            low_link[u] = min(low_link[u], s_time[v]);
        } else {
            // ignore cross-edge & forward-edge
        }
    }

    if (low_link[u] == s_time[u]) {
        scc_count++;

        int v;
        do {
            v = st.top();
            st.pop();
            on_stack[v] = false;
            scc[v] = u;
        } while (v != u);
    }

    vis[u] = 2;
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    G.assign(V+1, vector<int>());
    low_link.assign(V+1, 0);
    vis.assign(V+1, 0);
    s_time.assign(V+1, -1);
    on_stack.assign(V+1, false);
    scc.assign(V+1, -1);
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (vis[u] == 0)
            dfs(u);

    int label_idx = 0;
    unordered_map<int,int> label_map;
    for (int repr : scc) {
        if (label_map.find(repr) == label_map.end())
            label_map.insert({ repr, label_idx++ });
    }

    cout << scc_count << endl;
    for (int u = 1; u <= V; u++)
        cout << label_map[scc[u]] << " ";
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