// Round Trip (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;

// Time: O(V + E)
// Space: O(V + E)
 
vector<vector<int>> G;
vector<bool> on_stack;
vector<int> depth;
stack<int> st;

void print_cycle(int v) {
    cout << v << " ";
    int u;
    do {
        u = st.top();
        st.pop();
        on_stack[u] = false;
        cout << u << " ";
    } while (u != v);
}

bool dfs(int u, int dep) {
    st.push(u);
    on_stack[u] = true;
    depth[u] = dep;

    for (int v : G[u]) {
        if (!on_stack[v]) {
            bool trip_found = dfs(v, dep+1);
            if (trip_found)
                return true;
        }
        else {
            int cycle_len = depth[u] - depth[v] + 1;
            if (cycle_len > 2) {
                cout << (cycle_len+1) << endl;
                print_cycle(v);
                return true;
            }
        }
    }

    if (!st.empty()) {
        st.pop();
        on_stack[u] = false;
    }

    return false;
}

void solve(vector<pair<int,int>>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    on_stack.assign(V+1, false);
    depth.assign(V+1, -1);
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int u = 1; u <= V; u++)
        if (depth[u] == -1) {
            bool trip_found = dfs(u, 0);
            if (trip_found)
                return;
        }

    cout << "IMPOSSIBLE";
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

    solve(edges, V, E);
    
    return 0;
}