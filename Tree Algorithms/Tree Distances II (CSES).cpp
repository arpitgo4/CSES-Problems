// Tree Distances II (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)

/**
 * For this problem, we can metaphorically rotate/re-root the tree at
 * every node. All the subtrees underneath the said node will move up
 * in the cartesian coordinate and i.e. their depth will decrease while nodes
 * outside the said node will move down i.e. their depth will increase.
 * 
 * Notion of subtree being underneath a node comes from rooting the tree 
 * at some arbitrary node. Rooting also gives the notion of parent-child 
 * and ancestor relationships.
 * 
 * In general terms, tree is just a undirected connected graph with no cycles.
 * Rooting also gives the metaphorical directions to the edges connecting all
 * the nodes in tree.
*/

typedef long long ll;
typedef pair<int,int> edge;
 
vector<vector<int>> T;
vector<ll> sz, sum, dp;

void re_root(int u, int p, int N) {
    if (p == -1)
        dp[u] = sum[u];
    else {
        // push subtree up
        // dp[u] - sz[u]

        // pull rest of the tree down
        // dp[p]-dp[u] + N-sz[u]

        dp[u] = N + dp[p] - (2 * sz[u]);         
    }

    for (int v : T[u])
        if (v != p)
            re_root(v, u, N);
}

void dfs(int u, int p, int dep, int N) {
    sz[u] = 1;
    sum[u] = dep;

    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u, dep+1, N);

            sum[u] += sum[v];
            sz[u] += sz[v];
        }
    }
}

void solve(vector<edge>& edges, int N) {
    T.assign(N+1, vector<int>());
    sz.assign(N+1, 0);
    sum.assign(N+1, 0);
    dp.assign(N+1, 0);
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, -1, 0, N);
    re_root(1, -1, N);

    for (int u = 1; u <= N; u++)
        cout << dp[u] << " ";
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N);
    
    return 0;
}