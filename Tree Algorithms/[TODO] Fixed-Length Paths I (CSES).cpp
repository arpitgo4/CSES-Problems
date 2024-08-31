// Fixed-Length Paths I (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)

/**
 * There is no concept of LCA without rooting the tree!!
 * Rooting the tree defines the highest ancestor which further
 * leads to subsequent ancestors in the tree.
 * 
 * Centroid tree is the rooted tree. Concept of LCA is applicable 
 * on it. There are total O(N^2) pairs possible for N node tree, hence
 * O(N^2) paths. With centroid tree, we can represent O(N^2) paths
 * as a set of O(NlogN) paths, by breaking each path w.r.t. all ancestors.
 * Any node can have atmost O(logN) ancestors.
 * 
 * With general tree, our search space to find count of paths with K-edges
 * is O(N^2) but with centroid tree search space reduces to O(NlogN)
 * 
 * Time complexity for building centroid tree, O(NlogN)
 * 
 * Total time complexity for the problem will be,
 * Time: O(NlogN)
 * Space: O(N)
*/

typedef pair<int,int> edge;
 
int N, K, path_count;

vector<vector<int>> T;
vector<int> sz, dp;                             // dp[k] -> c, count of nodes at distance k from root of tree
vector<bool> removed;

void find_subtree_sz(int u, int p) {
    sz[u] = 1;
    for (int v : T[u]) {
        if (v != p) {
            find_subtree_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int find_centroid(int u, int p) {
    for (int v : T[u]) {
        if (v != p && !removed[v] && sz[v] > N/2)                                // sz[v] > N/2
            return find_centroid(v, u);
    }

    return u;
}

// dfs to count paths
// edge_count, count of edges from centroid of tree
void dfs(int u, int p, int edge_count) {
    if (edge_count <= K)
        path_count += dp[K-edge_count];

    for (int v : T[u]) {
        if (v != p && !removed[v]) {
            dfs(v, u, edge_count+1);
        }
    }

    dp[edge_count]++;
}

void decompose(int u, int p) {
    int centroid = find_centroid(u, p);

    dp.assign(N+1, 0);
    dp[0] = 1;
    dfs(centroid, -1, 0);

    removed[centroid] = true;
    for (int v : T[centroid]) {
        if (v != p && !removed[v]) {
            decompose(v, centroid);
        }
    }
}

void solve(vector<edge>& edges) {
    T.assign(N+1, vector<int>());
    sz.assign(N+1, 0);
    removed.assign(N+1, false);
    path_count = 0;
    for (auto& [u, v] : edges) {
        T[u].push_back(v);
        T[v].push_back(u);
    }

    find_subtree_sz(1, -1);
    decompose(1, -1);
    
    cout << path_count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> K;

    int u, v;
    vector<edge> edges(N-1);   
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges);
    
    return 0;
}