// Subtree Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;

// Time: O(N + N + QlogN)     // build euler tour & segment tree + per query on seg tree
// Space: O(N)

vector<vector<int>> T;
vector<ll> tree_val;
vector<int> euler_tour, s_time, e_time;
vector<ll> seg_tree;

int timer = 0;

ll update(int l, int h, int i, int idx, ll val) {
    if (l > h)
        return 0;
    if (l == h && l == idx)
        return seg_tree[i] = val;

    int m = (h-l)/2 + l;
    if (idx <= m) {
        ll left = update(l, m, 2*i+1, idx, val);
        return seg_tree[i] = left + seg_tree[2*i+2];
    } else {
        ll right = update(m+1, h, 2*i+2, idx, val);
        return seg_tree[i] = seg_tree[2*i+1] + right;
    }
}

ll query(int l, int h, int i, int p, int q) {
    if (l > h)
        return 0;
    if (l == p && h == q)
        return seg_tree[i];

    int m = (h-l)/2 + l;
    if (p <= m && q <= m)
        return query(l, m, 2*i+1, p, q);
    else if (p > m && q > m)
        return query(m+1, h, 2*i+2, p, q);

    return query(l, m, 2*i+1, p, m) + query(m+1, h, 2*i+2, m+1, q);
}

ll build_segment_tree(int l, int h, int i) {
    if (l > h)
        return 0;
    if (l == h)
        return seg_tree[i] = tree_val[euler_tour[l]];

    int m = (h-l)/2 + l;
    ll left = build_segment_tree(l, m, 2*i+1);
    ll right = build_segment_tree(m+1, h, 2*i+2);

    return seg_tree[i] = left + right;
}

void dfs(int u, int p) {
    s_time[u] = ++timer;
    euler_tour[timer] = u;

    for (int v : T[u])
        if (v != p)
            dfs(v, u);

    e_time[u] = ++timer;
    euler_tour[timer] = u;
}

void build_tree(vector<pair<int,int>>& edges, int N) {
    T.assign(N+1, vector<int>());
    euler_tour.assign(2*N+1, -1);
    s_time.assign(N+1, -1);
    e_time.assign(N+1, -1);
    seg_tree.assign(8*N+4, 0);
    
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

    tree_val.assign(N+1, 0);
    for (int i = 1; i < N+1; i++)
        cin >> tree_val[i];

    int u, v;
    vector<pair<int,int>> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    build_tree(edges, N);
    dfs(1, 1);                                 // builds euler tour
    build_segment_tree(1, 2*N, 0);

    int type, node, val;
    for (int i = 0; i < Q; i++) {
        cin >> type >> node;
        if (type == 1) {
            cin >> val;
            tree_val[node] = val;
            update(1, 2*N, 0, s_time[node], val);
            update(1, 2*N, 0, e_time[node], val);
        } else 
            cout << (query(1, 2*N, 0, s_time[node], e_time[node])/2) << endl;
    }
    
    return 0;
}