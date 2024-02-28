// Finding a Centroid (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N + (N-1)) ~ O(N)
// Space: O(N + (N-1)) ~ O(N)

vector<vector<int>> T;
vector<int> degree;

int centroid_decomposition(vector<vector<int>>& T, int N) {
    if (N < 3)
        return 1;

    vector<int> layer;
    for (int u = 1; u <= N; u++)
        if (degree[u] == 1)
            layer.push_back(u);

    int total_nodes = N;
    while (total_nodes > 2) {

        vector<int> next_layer;
        for (int u : layer) {
            for (int v : T[u]) {
                degree[v]--;
                if (degree[v] == 1)
                    next_layer.push_back(v);
            }

            total_nodes--;
        }

        layer = next_layer;
    }

    return layer[0];
}

void solve(int N, vector<pair<int,int>>& edges) {
    T.assign(N+1, vector<int>());
    degree.assign(N+1, 0);

    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
        degree[u] = T[u].size();
        degree[v] = T[v].size();
    }

    int centroid = centroid_decomposition(T, N);

    cout << centroid;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<pair<int,int>> edges(N-1);
    int u, v;
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(N, edges);

    return 0;
}