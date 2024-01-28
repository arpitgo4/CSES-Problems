// Distance Queries (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
 
// Euler tour + Sparse Table (build: O(NlogN)) (find LCA in O(1))
// Logic for distance between two nodes O(1)

// Kept two separate sparse tables (depth values & node ids)

// Time: O(NlogN + Q)
// Space: O(NlogN)

vector<vector<int>> T, sparse_table_depth, sparse_table_val;
vector<int> euler_tour, s_time, e_time, depth;

int timer = 0;

// min sparse table
void build_sparse_table() {
    int N = euler_tour.size();
    int max_pow = ceil(log2(N));
    sparse_table_depth.assign(max_pow + 1, vector<int>(N+1, -1));
    sparse_table_val.assign(max_pow + 1, vector<int>(N+1, -1));

    for (int i = 1; i < N; i++) {
        sparse_table_depth[0][i] = depth[euler_tour[i]];
        sparse_table_val[0][i] = euler_tour[i];
    }

    for (int pow = 1; pow <= max_pow; pow++)
        for (int i = 1; i < N; i++) {
            int a = sparse_table_depth[pow-1][i];
            int b = INT_MAX;
            int b_idx = i + (1 << (pow-1));
            if (b_idx < N+1)
                b = sparse_table_depth[pow-1][b_idx];

            if (a < b) 
                sparse_table_val[pow][i] = sparse_table_val[pow-1][i];
            else sparse_table_val[pow][i] = sparse_table_val[pow-1][b_idx];

            sparse_table_depth[pow][i] = min(a, b);
        }
}

int query(int i, int j) {
    int dist = j-i+1;
    int pow = log2(dist);

    int a = sparse_table_depth[pow][i];
    int b = sparse_table_depth[pow][j-(1 << pow)+1];

    if (a < b)
        return sparse_table_val[pow][i];
    else return sparse_table_val[pow][j-(1 << pow)+1];
}

void dfs(int u, int p, int dep) {
    s_time[u] = ++timer;
    euler_tour[s_time[u]] = u;
    depth[u] = dep;

    for (int v : T[u])
        if (v != p) {
            dfs(v, u, dep+1);
            euler_tour[++timer] = u;
        }

    e_time[u] = timer;
}

void build_tree(vector<pair<int,int>>& edges, int N) {
    T.assign(N+1, vector<int>());
    s_time.assign(N+1, -1);
    e_time.assign(N+1, -1);
    depth.assign(N+1, -1);
    euler_tour.assign(2*N, -1);   // every edge is repeated twice, 2N-2 edges, 2N-1 index + 1 padding = 2N
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;

    int u, v;
    vector<pair<int,int>> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    build_tree(edges, N);
    dfs(1, -1, 0);                          // builds euler tour
    build_sparse_table();

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;

        int lca = query(min(s_time[u], s_time[v]), max(e_time[u], e_time[v]));

        // 2*depth[lca] - depth[u] - depth[v];
        int dist = abs(depth[lca] - depth[u]) + abs(depth[lca] - depth[v]);
        cout << dist << endl;
    }
    
    return 0;
}