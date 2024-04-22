// Fixed-Length Paths I (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)

// Time: O(N^2)
// Space: O(N)
 
/**
 * Did Centroid Decomposition on given tree
 * Each path from root to leaf is of length O(logN)
 * 
 * Centroid Decomposition can also be used for finding
 * LCA in O(logN) time.
 * 
 * Brute force solution,
 * 1. For every pair of node, check if distance(a, b) == K
 * 
 * Distance between any pair of nodes goes through there LCA.
 * distance(a, b) = distance(a, lca(a, b)) + distance(b, lca(a, b))
*/

typedef pair<int,int> edge;
 
vector<set<int>> T;
vector<vector<int>> CT;
vector<edge> centroid_edges;
vector<int> sz, s_time, e_time, depth, P;
vector<int> dp;

int timer = 0;
int counter = 0;
int max_depth = 0;

void dfs4(int u, int p, int dep, bool contribute, int K) {
    if (dep > K)
        return;
    max_depth = max(max_depth, dep);

    if (contribute) {
        counter += dp[K-dep];
    } else {
        dp[dep]++;
    }

    for (int v : CT[u])
        if (v != p)
            dfs4(v, u, dep+1, contribute, K);
}

void dfs3(int u, int p, int K, int N) {
    max_depth = 0;
    dp[0] = 1;
    for (int v : CT[u]) {
        if (v != p) {
            dfs4(v, u, 1, true, K);
            dfs4(v, u, 1, false, K);
        }
    }

    for (int i = 0; i <= max_depth; i++)
        dp[i] = 0;

    for (int v : CT[u]) {
        if (v != p) {
            dfs3(v, u, K, N);
        }
    }
}

bool is_ancestor(int a, int b) {
    return s_time[a] <= s_time[b] && e_time[b] <= e_time[a];
}

int distance(int a, int b, int N) {
    if (is_ancestor(a, b) || is_ancestor(b, a)) 
        return abs(depth[a] - depth[b]);

    int u = a, v = b;
    for (int i = 0; i < log2(N) && u != v; i++) {
        if (depth[u] > depth[v])
            u = P[u];
        else if (depth[u] < depth[v])
            v = P[v];
        else {
            u = P[u];
            v = P[v];
        }
    }

    return depth[a] + depth[b] - (2 * depth[u]);
}

void dfs2(int u, int p, int dep) {
    s_time[u] = timer++;
    depth[u] = dep;
    P[u] = p;

    for (int v : CT[u]) {
        if (v != p) {
            dfs2(v, u, dep+1);
        }
    }

    e_time[u] = timer++;
}

void build_centroid_tree(vector<edge>& edges, int N) {
    CT.assign(N+1, vector<int>());
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        CT[u].push_back(v);
        CT[v].push_back(u);
    }
}

int find_centroid(int u, int p, int N) {
    for (int v : T[u]) {
        if (v != p && sz[v] > N/2)
            return find_centroid(v, u, N);
    }

    return u;
}

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

void decompose(int u, int p_centroid, int N) {
    sz.assign(N+1, 0);
    dfs(u, -1);

    int centroid = find_centroid(u, -1, N);
    if (p_centroid != -1)
        centroid_edges.push_back({ p_centroid, centroid });

    vector<int> roots;
    for (int v : T[centroid]) {
        T[v].erase(centroid);
        roots.push_back(v);
    }
    T[centroid].clear();

    for (int v : roots)
        decompose(v, centroid, N);
}

void solve(vector<edge>& edges, int N, int K) {
    T.assign(N+1, set<int>());
    P.assign(N+1, -1);
    depth.assign(N+1, 0);
    s_time.assign(N+1, 0);
    e_time.assign(N+1, 0);
    dp.assign(N+1, 0);
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].insert(v);
        T[v].insert(u);
    }

    decompose(1, -1, N);
    build_centroid_tree(centroid_edges, N);

    dfs2(1, -1, 0);

    dfs3(1, -1, K, N);

    cout << counter << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    cin >> N >> K;

    int u, v;
    vector<edge> edges(N-1);   
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N, K);
    
    return 0;
}