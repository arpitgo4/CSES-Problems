// Path Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;
 
vector<vector<int>> T;
vector<ll> tree_val;
vector<int> euler_tour, s_time, e_time;

int timer = 0;

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
    // seg_tree.assign(8*N+4, 0);
    
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

    int type, node, val;
    for (int i = 0; i < Q; i++) {
        cin >> type >> node;
        if (type == 1) {
            cin >> val;
            tree_val[node] = val;
            // update(1, 2*N, 0, s_time[node], val);
            // update(1, 2*N, 0, e_time[node], val);
        } else {
            // cout << (query(1, 2*N, 0, s_time[node], e_time[node])/2) << endl;
        }
    }
    
    return 0;
}