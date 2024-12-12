// Road Construction (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Time: O(⍺(V))
// Space: O(V)

typedef pair<int,int> edge;

vector<int> P, S;

void dsu_init(int V) {
    P.assign(V+1, -1);
    S.assign(V+1, 1);
    for (int i = 0; i <= V; i++)
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

        P[root_y] = P[root_x];
        S[root_x] += S[root_y];
        S[root_y] = -1;
    }
}

void solve(int V, vector<edge>& edges, int E) {
    dsu_init(V);

    int comp_cnt = V, sz_comp = 1;
    for (auto& [u, v] : edges) {
        if (root(u) != root(v)) {
            union_set(u, v);

            comp_cnt--;
            sz_comp = max(sz_comp, max(S[root(u)], S[root(v)]));
        }

        cout << comp_cnt << " " << sz_comp << endl;
    }
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

    solve(V, edges, E);

    return 0;
}