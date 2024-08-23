// Range Update Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
typedef long long ll;

vector<ll> ST, A, lazy;

void build_seg_tree(int l, int h, int i) {
    if (l == h) {
        ST[i] = A[l];
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

void push(int i) {
    if (lazy[i] != 0) {
        lazy[2*i+1] += lazy[i];
        lazy[2*i+2] += lazy[i];
        lazy[i] = 0;
    }
}

void update(int l, int h, int i, int p, int q, ll x) {
    if (l > h || p > h || l > q)
        return;
    if (l == p && h == q) {
        lazy[i] += x;
        return;
    }

    if (l != h)                                                 // internal node
        push(i);

    int m = (h-l)/2 + l;
    update(l, m, 2*i+1, p, min(m, q), x);
    update(m+1, h, 2*i+2, max(m+1, p), q, x);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

ll query(int l, int h, int i, int k) {
    if (l > h)
        return 0;
    if (l == h && l == k)
        return ST[i] + lazy[i];                                 // reading only single element at a time

    if (l != h)                                                 // internal node
        push(i);

    int m = (h-l)/2 + l;
    if (k <= m)
        return query(l, m, 2*i+1, k);
    else return query(m+1, h, 2*i+2, k);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    
    A.assign(N, 0);
    ST.assign(4*N, 0);
    lazy.assign(4*N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int type, l, h, k;
    ll x;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> l >> h >> x;
            update(0, N-1, 0, l-1, h-1, x);
        } else {
            cin >> k;
            ll val = query(0, N-1, 0, k-1);
            cout << val << endl;
        }
    }
    
    return 0;
}