// Building Roads (CSES)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time: O(E*⍺(V) + V*⍺(V)) ~ O(V + E)
// Space: O(V + E)

typedef pair<int,int> edge;

vector<int> P, S;

void init_dsu(int N) {
    P.assign(N+1, -1);
    S.assign(N+1, 1);
    for (int i = 0; i <= N; i++)
        P[i] = i;
}

int root(int x) {
    if (P[x] != x)
        P[x] = root(P[x]);

    return P[x];
}

void union_set(int x, int y) {
    int root_x = root(x);
    int root_y = root(y);
    if (root_x != root_y) {
        if (S[root_x] < S[root_y])
            swap(root_x, root_y);

        P[root_y] = root_x;
        S[root_x] += S[root_y];
    }
}

void solve(int V, vector<edge>& edges, int E) {
    init_dsu(V);

    int comp_cnt = V;
    for (auto& [u, v] : edges) {
        if (root(u) != root(v)) {
            union_set(u, v);
            comp_cnt--;
        }
    }

    cout << (comp_cnt-1) << endl;
    int prev_root = -1;
    for (int u = 1; u <= V; u++) {
        if (root(u) == u) {
            if (prev_root != -1)
                cout << prev_root << " " << u << endl;

            prev_root = u;
        }
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

    solve(V, edges, E);

    return 0;
}