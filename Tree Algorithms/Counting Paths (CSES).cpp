// Counting Paths (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
 
// Time: O(NlogN + M + N)               // NlogN: sparse table pre-processing, M: range updates, N: DFS traversals
// Space: O(NlogN + N)                  // NlogN: sparse table, N: stack size for DFS traversals
 
#define INF INT_MAX

typedef pair<int,int> edge;
 
/**
 * turn the problem around
 * for each path, traverse it and maintain count pointers for each
 * node that you encounter.
 * 
 * LCA pre-processing for tree,
 *  1. Euler tour, O(N)
 *  2. Segment tree or Sparse table O(N), O(NlogN)
 *  3. Find LCA and traverse from a and b and update counters for nodes you see.
 * 
 * Time: O(NlogN + M * diameter)        // NlogN: sparse table, M * diameter: max length of any path in tree is its diameter
 * Space: O(NlogN + N)                  // NlogN: sparse table, N: counter vector
 * 
 * In skewed tree, with all nodes (N) stacked in form of a linked list
 * diameter = N
 * Time: O(NlogN + (M * N))             // M * N: will cause TLE
 * 
 * Above solution, does gives TLE for some test cases
 * 
 * Time: O(NlogN + (M * Diameter))
 * Space: O(NlogN + N)
 * 
 * 
 * Problem can be solved efficiently by using a range update technique in which
 * range will the sub-paths from lca to a & b. After all the update operations
 * single DFS traversal can be used to get the final values for each node.
 * Difference Array technique can be used for range update operations. Difference
 * array is useful for O(1) range updates and O(N) retrievals.
 * 
 * In this problem, we have M range update operation and only one retrieval at the end.
 * 
 * Time: O(NlogN + M + N)               // NlogN: sparse table pre-processing, M: range updates, N: DFS traversals
 * Space: O(NlogN + N)                  // NlogN: sparse table, N: stack size for DFS traversals
*/

vector<vector<int>> T, ST;
vector<int> euler_tour, P;
vector<int> s_time, e_time, depth;
vector<int> dp;

int timer = 0;

// minimum sparse table
void build_sparse_table() {
    int N = euler_tour.size();
    int max_pow = log2(N);
    ST.assign(max_pow+1, vector<int>(N, INF));

    for (int i = 0; i < N; i++)
        ST[0][i] = euler_tour[i];

    for (int pow = 1; pow <= max_pow; pow++)
        for (int i = 0; i < N; i++) {
            int a = ST[pow-1][i];
            int b_idx = i + (1 << (pow-1));
            int b = INF;
            if (b_idx < N)
                b = ST[pow-1][b_idx];

            if (b == INF || depth[a] < depth[b])
                ST[pow][i] = a;
            else ST[pow][i] = b;
        }
}

void dfs(int u, int p, int dep) {
    s_time[u] = timer++;
    euler_tour[s_time[u]] = u;
    depth[u] = dep;
    P[u] = p;

    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u, dep+1);
            euler_tour[timer++] = u;
        }
    }

    e_time[u] = timer-1;
}

int query_lca(int l, int h) {
    int w_size = h-l+1;
    int pow = log2(w_size);
    int a = ST[pow][l];
    int b = ST[pow][h-(1<<pow)+1];
    if (depth[a] < depth[b])
        return a;
    else return b;
}

void build_tree(vector<edge>& edges, int N, vector<edge>& paths, int M) {
    T.assign(N+1, vector<int>());
    P.assign(N+1, -1);
    s_time.assign(N+1, -1);
    e_time.assign(N+1, -1);
    depth.assign(N+1, 0);
    dp.assign(N+1, 0);
    euler_tour.assign(2*N-1, -1);
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }
}

void dfs2(int u, int p) {
    for (int v : T[u]) {
        if (v != p) {
            dfs2(v, u);
            dp[u] += dp[v];
        }
    }
}

bool is_ancestor(int a, int b) {
    return s_time[a] <= s_time[b] && e_time[b] <= e_time[a];
}

void solve(vector<edge>& edges, vector<edge>& paths, int M, int N) {
    build_tree(edges, N, paths, M);

    dfs(1, -1, 0);
    build_sparse_table();

    for (edge& e : paths) {
        int a = e.first, b = e.second;
        int lca = query_lca(
            min(s_time[a], s_time[b]),
            max(e_time[a], e_time[b])
        );

        if (is_ancestor(a, b)) {
            dp[b]++;
        } else if (is_ancestor(b, a)) {
            dp[a]++;
        } else {
            dp[a]++;
            dp[b]++;
            dp[lca]--;
        }

        if (lca != 1)
            dp[P[lca]]--;
    }

    dfs2(1, -1);

    for (int u = 1; u <= N; u++)
        cout << dp[u] << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    vector<edge> paths(M);
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        paths[i] = { u, v };
    }

    solve(edges, paths, M, N);
    
    return 0;
}