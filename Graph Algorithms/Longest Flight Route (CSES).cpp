// Longest Flight Route (CSES)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Time: O(V + E)
// Space: O(V + E)

/**
 * No need to do topological sort first. As problem states that the flight network is a DAG and we already have the
 * starting point city-1. Dynamic Programming is enough to find the longest route in the given DAG.
*/

vector<vector<int>> G;
vector<int> cache;
vector<int> NEXT;

int dfs(int u, int dest) {
    if (u == dest)
        return 0;
    if (cache[u] != -1)
        return cache[u];

    int max_count = INT_MIN;
    for (int v : G[u]) {
        int count = 1 + dfs(v, dest);
        if (count > max_count) {
            max_count = count;
            NEXT[u] = v;
        }
    }

    return cache[u] = max_count;
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    cache.assign(V+1, -1);
    NEXT.assign(V+1, -1);
    G.assign(V+1, vector<int>());

    for (pair<int,int>& p : edges) {
        int u = p.first, v = p.second;
        G[u].push_back(v);
    }

    int count = dfs(1, V);

    if (count < 0)
        cout << "IMPOSSIBLE";
    else {
        cout << (count+1) << endl;
        int u = 1;
        while (u != -1) {
            cout << u << " ";
            u = NEXT[u];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<pair<int,int>> edges(E);
    int u, v;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(V, E, edges);

    return 0;
}