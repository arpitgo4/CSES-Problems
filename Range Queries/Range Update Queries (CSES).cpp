// Range Update Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
/**
 * With lazy propogation model,
 * 
 * For `update` call, targetted node is marked and lazy update value
 * is recorded. This makes the range updates `O(logN)`
 * 
 * For further `query` or `update` call, if a node has a marker on it
 * new value is updated for it and lazy update is propogated further 
 * down the tree.
 * Above, optimization makes sure, we only propogate updates down the tree
 * step-by-step and only where we need to propogate. Otherwise, with eager
 * propogation time complexity will become `O(NlogN)`.
 * 
 * For `query` call specially, we need to check whether there is a lazy update
 * pending on the node or not before reading it's value. 
 * This is the case for leaf nodes where lazy updates can't be propogated further
 * and there new values are updated in any of the previous queries.
 */

typedef long long ll;

vector<ll> ST, A, lazy;
vector<bool> marked;

void build_seg_tree(int l, int h, int i) {
    if (l > h)
        return;
    if (l == h) {
        ST[i] = A[l];
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    ST[i] = ST[2*i+1] + ST[2*i+2];    
}

void push(int l, int h, int i) {
    if (marked[i]) {
        lazy[2*i+1] += lazy[i];
        lazy[2*i+2] += lazy[i];
        marked[2*i+1] = marked[2*i+2] = true;

        ST[i] += (lazy[i] * (h-l+1));
        lazy[i] = 0;
        marked[i] = false;
    }
}

void update(int l, int h, int i, int p, int q, ll x) {
    if (p > q)
        return;
    if (l == p && h == q) {
        marked[i] = true;
        lazy[i] += x;
        return;
    }

    push(l, h, i);
    int m = (h-l)/2 + l;
    update(l, m, 2*i+1, p, min(q, m), x);
    update(m+1, h, 2*i+2, max(m+1, p), q, x);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

ll query(int l, int h, int i, int k) {
    if (l == h && l == k)
        return marked[i] ? ST[i] + lazy[i] : ST[i];
    
    push(l, h, i);
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
    marked.assign(4*N, false);
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