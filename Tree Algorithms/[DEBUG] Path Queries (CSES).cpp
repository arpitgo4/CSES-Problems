// Path Queries (CSES)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Time: O(N + N + QlogN)
// Space: O(N)

typedef long long ll;
typedef pair<int,int> edge;

/**
 * Test Cases with big numbers and big tree size are failing
 * 
 * Should be due to number overflow somewhere...!
*/

vector<vector<int>> T;
vector<int> LT, sz, s_time;
vector<ll> val, sum;

vector<ll> ST, lazy;
vector<bool> marked;

int timer = 0;

void print_vector(vector<int>& A) {
    for (int a : A)
        cout << a << " ";
    cout << endl;
}
void print_vector(vector<ll>& A) {
    for (ll a : A)
        cout << a << " ";
    cout << endl;
}

void build_seg_tree(int l, int h, int i) {
    if (l > h)
        return;
    if (l == h) {
        ST[i] = sum[l];
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

void push(int i) {
    if (marked[i]) {
        lazy[2*i+1] += lazy[i];
        lazy[2*i+2] += lazy[i];
        marked[2*i+1] = marked[2*i+2] = true;

        lazy[i] = 0;
        marked[i] = false;
    }
}

void update(int l, int h, int i, int p, int q, ll x) {
    if (p > q)
        return;
    if (l == p && h == q) {
        lazy[i] += x;
        marked[i] = true;
        return;
    }

    push(i);

    int m = (h-l)/2 + l;
    update(l, m, 2*i+1, p, min(q, m), x);
    update(m+1, h, 2*i+2, max(m+1, p), q, x);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

ll query(int l, int h, int i, int k) {
    if (l == h && l == k)
        return ST[i] + lazy[i];

    push(i);

    int m = (h-l)/2 + l;
    if (k <= m)
        return query(l, m, 2*i+1, k);
    else return query(m+1, h, 2*i+2, k);
}

void dfs(int u, int p, ll acc) {
    s_time[u] = timer++;
    LT[s_time[u]] = u;
    sz[s_time[u]] = 1;
    sum[s_time[u]] = acc + val[u];

    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u, sum[s_time[u]]);
            sz[s_time[u]] += sz[s_time[v]];
        }
    }
}

void build_tree(vector<edge>& edges, int N) {
    T.assign(N+1, vector<int>());
    s_time.assign(N+1, -1);
    LT.assign(N, -1);
    sum.assign(N, 0);
    sz.assign(N, 0);
    ST.assign(4*N, 0);
    lazy.assign(4*N, 0);
    marked.assign(4*N, false);
    for (auto& [u, v] : edges) {
        T[u].push_back(v);
        T[v].push_back(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;

    val.assign(N+1, 0);
    for (int i = 1; i <= N; i++)
        cin >> val[i];

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    build_tree(edges, N);
    dfs(1, -1, 0);                                              // linearizes tree
    build_seg_tree(0, N-1, 0);

    // cout << "Arrays: " << endl;
    // print_vector(s_time);
    // print_vector(LT);
    // print_vector(sz);
    // print_vector(val);
    // print_vector(sum);
    // print_vector(ST);

    int type;
    ll x;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> u >> x;
            update(0, N-1, 0, s_time[u], s_time[u]+sz[s_time[u]]-1, x-val[u]);
        } else {
            cin >> u;
            ll val = query(0, N-1, 0, s_time[u]);
            cout << val << endl;
        }
    }
    
    return 0;
}