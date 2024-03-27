// Flight Routes Check (CSES)

#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
typedef pair<int,int> edge;
 
vector<vector<int>> G;
vector<int> vis, low_link, s_time;
vector<int> scc_roots, P;          // P, path-compressed parent-pointer tree
vector<bool> on_stack;
stack<int> st;

int timer = 0;

void dfs(int u) {
    low_link[u] = s_time[u] = timer++;
    st.push(u);
    on_stack[u] = true;
    vis[u] = 1;

    for (int v : G[u]) {
        if (vis[v] == 0) {                                  // tree-edge
            dfs(v);
            low_link[u] = min(low_link[u], low_link[v]);
        } else if (on_stack[v]) {                           // back-edge
            low_link[u] = min(low_link[u], s_time[v]);
        } else {
                                                            // cross-edge or forward edge
            // vis[v] == 1 || on_stack[v] == false
            // v is visited before OR v is not on stack (not an ancestor)
            // if v is not on stack that means it's outside of current DFS tree
            // but it can also be an upcoming child vertex (i.e. forward edge)
        }
    }

    if (low_link[u] == s_time[u]) {
        int v;
        do {
            v = st.top();
            st.pop();
            on_stack[v] = false;
            P[v] = u;
        } while (v != u);

        scc_roots.push_back(u);
    }
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    vis.assign(V+1, 0);
    s_time.assign(V+1, -1);
    low_link.assign(V+1, -1);
    P.assign(V+1, -1);
    on_stack.assign(V+1, false);
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
    }

    for (int u = 1; u <= V; u++)
        if (vis[u] == 0)
            dfs(u);

    if (scc_roots.size() == 1) {
        cout << "YES" << endl;
        return;
    } else {
        cout << "NO" << endl;
        for (edge& e : edges) {
            int u = e.first, v = e.second;
            if (P[u] != P[v]) {
                cout << v << " " << u << endl;
                return;
            }
        }

        cout << scc_roots[0] << " " << scc_roots[1] << endl;     // if the condensed graph is disconnected
    }
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