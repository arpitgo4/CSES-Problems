// Message Route (CSES)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// BFS traversal for un-weighted graphs produces minimum distance from source to destination
// Time: O(V + E)
// Space: O(V + E)

typedef pair<int,int> edge;

vector<vector<int>> G;
vector<int> vis, path;
vector<int> P;                                      // shortest-path tree

void bfs(int src, int dest) {
    queue<int> q;
    q.push(src);
    vis[src] = 1;                                       // avoids any back-edge to source vertex from adding it back in queue and making a loop in shortest-path tree

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : G[u]) {
            if (vis[v] == 0) {
                vis[v] = 1;                             // avoids duplicate entries for same vertex into queue
                P[v] = u;
                q.push(v);
            }
        }
    }
}

void solve(vector<edge>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    vis.assign(V+1, 0);
    P.assign(V+1, -1);
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bfs(1, V);

    if (vis[V] == 0) {
        cout << "IMPOSSIBLE";
        return;
    }

    int curr = V;
    while (curr != -1) {
        path.push_back(curr);
        curr = P[curr];
    }

    reverse(path.begin(), path.end());

    cout << path.size() << endl;
    for (int u : path)
        cout << u << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<edge> edges(E);
    int u, v;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, V, E);

    return 0;
}