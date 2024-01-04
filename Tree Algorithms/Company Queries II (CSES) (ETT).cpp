// Company Queries II (CSES) (ETT)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
using ll = long long;
 
// Time: O(N + NlogN + Q)       // builds euler tour & sparse table + O(1) per query
// Space: O(NlogN)

vector<vector<int>> sparse_table;
vector<vector<int>> T;
vector<int> euler_tour, s_time, e_time, depth;
int timer = 0;

void print_vector(vector<int>& A) {
    int N = A.size();
    for (int i = 1; i < N; i++)
        cout << A[i] << " ";
    cout << endl;
}

void print_vector(vector<vector<int>>& A) {
    for (vector<int>& v : A) {
        for (int a : v)
            if (a != INT_MAX)
                cout << a << " ";
        cout << endl;
    }
}

void build_sparse_table() {
    int N = euler_tour.size();
    int max_pow = ceil(log2(N)) + 1;
    sparse_table.assign(max_pow, vector<int>(N+1, INT_MAX));

    for (int i = 1; i < N; i++)
        sparse_table[0][i] = euler_tour[i];

    for (int pow = 1; pow < max_pow; pow++)
        for (int i = 1; i < N; i++) {
            int a = sparse_table[pow-1][i];

            int b_idx = i + (1 << (pow-1));
            int b = b_idx < N ? sparse_table[pow-1][b_idx] : INT_MAX;

            if (b != INT_MAX && depth[a] < depth[b])
                sparse_table[pow][i] = a;
            else sparse_table[pow][i] = b;
        }
}

int query_sparse_table(int l, int h) {
    int size = h-l+1;
    int pow = log2(size);

    int a = sparse_table[pow][l];
    int b = sparse_table[pow][h-(1<<pow)+1];

    return depth[a] < depth[b] ? a : b;
}

void dfs(int u, int p, int dep) {
    s_time[u] = ++timer;
    euler_tour[timer] = u;
    depth[u] = dep;

    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u, dep+1);
            euler_tour[++timer] = u;
        }
    }

    e_time[u] = timer;
}

void build_tree(vector<pair<int,int>>& edges, int N) {
    T.assign(N+1, vector<int>());
    euler_tour.assign(2*N, -1);         // 2N-1 nodes
    s_time.assign(N+1, 0);
    e_time.assign(N+1, 0);
    depth.assign(N+1, INT_MAX);

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

    int p;
    vector<pair<int,int>> edges;
    for (int i = 2; i <= N; i++) {
        cin >> p;
        edges.push_back({ p, i });
    }

    build_tree(edges, N);
    dfs(1, 1, 0);
    build_sparse_table();

    int u, v;
    vector<int> res;
    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        int l = min(s_time[u], e_time[v]);
        int h = max(s_time[u], e_time[v]);
        res.push_back(query_sparse_table(l, h));
    }

    for (int r : res)
        cout << r << endl;
    
    return 0;
}