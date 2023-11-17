// Road Reparation (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<int> P, S;

void init_dsu(int V) {
    P.assign(V+1, 0);
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
    if (root_x == root_y)
        return;

    if (S[root_x] >= S[root_y]) {
        P[root_y] = P[root_x];
        S[root_x] += S[root_y];
        S[root_y] = -1;
    } else {
        P[root_x] = P[root_y];
        S[root_y] += S[root_x];
        S[root_x] = -1;
    }
}

void mst(int V, vector<tuple<int,int,int>>& edges) {
    auto comp = [&](const tuple<int,int,int>& t1, const tuple<int,int,int>& t2) {
        return get<2>(t1) < get<2>(t2);
    };
    sort(edges.begin(), edges.end(), comp);

    ll cost = 0;
    int num_comps = V;
    for (tuple<int,int,int>& t : edges) {
        int u, v, w;
        tie(u, v, w) = t;

        if (root(u) != root(v)) {
            union_set(u, v);
            cost += (ll) w;
            num_comps--;
        }
    }

    if (num_comps > 1)
        cout << "IMPOSSIBLE";
    else cout << cost;
}

void solve(int V, int E, vector<tuple<int,int,int>>& edges) {
    init_dsu(V);

    mst(V, edges);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<tuple<int,int,int>> edges(E);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(V, E, edges);

    return 0;
}