// Message Route (CSES)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// BFS traversal for non-weighted graphs produces minimum distance from source to destination
// Time: O(V + E)
// Space: O(V + E)


vector<int> VIS;
vector<int> P;
vector<int> path;

void prepare_path(int u) {
    while (u != -1) {
        path.push_back(u);
        u = P[u];
    }
}

bool bfs(vector<vector<int>>& G, int src, int dest) {
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        VIS[u] = 1;

        if (u == dest) {
            prepare_path(u);
            return true;
        }

        for (int v : G[u])
            if (VIS[v] == 0) {
                q.push(v);
                P[v] = u;
            }
    }

    return false;
}

void solve(vector<vector<int>>& G, int V, int E) {
    VIS.assign(V+1, 0);
    P.assign(V+1, -1);

    bool path_found = bfs(G, 1, V);
    if (!path_found) {
        cout << "IMPOSSIBLE";
        return;
    }

    int N = path.size();
    cout << N << endl;
    for (int i = N-1; i >= 0; i--)
        cout << path[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<vector<int>> G(V+1, vector<int>());
    int u, v;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    solve(G, V, E);

    return 0;
}