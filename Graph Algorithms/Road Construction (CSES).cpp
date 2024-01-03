// Road Construction (CSES)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Time: O(log*(V)) -> O(1)
// Space: O(V)

vector<int> P, S;

void dsu_init(int V) {
    P.assign(V+1, 0);
    S.assign(V+1, 1);
    for (int i = 0; i <= V; i++)
        P[i] = i;
}

int root(int u) {
    if (P[u] != u)
        P[u] = root(P[u]);

    return P[u];
}

void union_set(int u, int v) {
    int root_u = root(u);
    int root_v = root(v);
    if (root_u == root_v)
        return;

    if (S[root_u] >= S[root_v]) {
        P[root_v] = P[root_u];
        S[root_u] += S[root_v];
        S[root_v] = -1;
    } else {
        P[root_u] = P[root_v];
        S[root_v] += S[root_u];
        S[root_u] = -1;
    }
}

void solve(int V, vector<pair<int,int>>& edges, int E) {
    dsu_init(V);

    int max_size = INT_MIN, num_sets = V;
    for (pair<int,int>& p : edges) {
        int u = p.first, v = p.second;

        if (root(u) != root(v)) {
            union_set(u, v);
            max_size = max({ max_size, S[root(u)], S[root(v)] });
            num_sets--;
        }

        cout << num_sets << " " << max_size << endl;
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

    solve(V, edges, E);

    return 0;
}