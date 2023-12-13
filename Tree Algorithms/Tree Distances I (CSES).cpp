// Tree Distances I (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N)
// Space: O(N)

vector<vector<int>> T;
vector<int> dp_down, dp_up;
vector<int> max_node_down, max1, max2;

int dfs(int u, int p) {
    for (int v : T[u])
        if (v != p) {
            int dist = 1 + dfs(v, u);
            if (dist > max1[u]) {
                max2[u] = max1[u];
                max1[u] = dist;
                max_node_down[u] = v;
            }
            else if (dist > max2[u])
                max2[u] = dist;
        }

    dp_down[u] = max1[u];

    return dp_down[u];
}

void re_root(int u, int p) {
    if (p != -1) {
        int max_up_dist = 0;
        if (max_node_down[p] != u)
            max_up_dist = 1 + max1[p];
        else max_up_dist = 1 + max2[p];

        dp_up[u] = max(max_up_dist, 1 + dp_up[p]);
    }

    for (int v : T[u])
        if (v != p)
            re_root(v, u);
}

void solve(vector<pair<int,int>>& E, int V) {
    T.assign(V+1, vector<int>());
    dp_down.assign(V+1, 0);
    dp_up.assign(V+1, 0);
    max_node_down.assign(V+1, -1);
    max1.assign(V+1, 0);
    max2.assign(V+1, 0);

    for (pair<int,int>& e : E) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, -1);
    re_root(1, -1);

    for (int u = 1; u < V+1; u++)
        cout << max(dp_down[u], dp_up[u]) << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V;
    cin >> V;

    vector<pair<int,int>> E(V-1);
    int u, v;
    for (int i = 0; i < V-1; i++) {
        cin >> u >> v;
        E[i] = { u, v };
    }

    solve(E, V);

    return 0;
}