// Range Updates and Sums (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
typedef long long ll;

vector<ll> A, ST, lazy_assign, lazy_add;

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

void push(int i) {
    if (lazy_add[i] != 0) {
        lazy_add[2*i+1] += lazy_add[i];
        lazy_add[2*i+2] += lazy_add[i];
        lazy_add[i] = 0;
    }
    if (lazy_assign[i] != 0) {
        lazy_assign[2*i+1] = lazy_assign[i];
        lazy_assign[2*i+2] = lazy_assign[i];
        lazy_assign[i] = 0;
    }
}

ll query(int l, int h, int i, int p, int q) {
    return -1;
}

void update_assign(int l, int h, int i, int p, int q, ll x) {
    if (l > h || p > q)
        return;
    if (l == p && h == q) {
        lazy_assign[i] = x;
        return;
    }

    push(i);

    int m = (h-l)/2 + l;
    update_assign(l, m, 2*i+1, p, min(q, m), x);
    update_assign(m+1, h, 2*i+2, max(m+1, p), q, x);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

void update_add(int l, int h, int i, int p, int q, ll x) {
    if (l > h || p > q)
        return;
    if (l == p && h == q) {
        lazy_add[i] += x;
        return;
    }

    push(i);

    int m = (h-l)/2 + l;
    update_add(l, m, 2*i+1, p, min(q, m), x);
    update_add(m+1, h, 2*i+2, max(m+1, p), q, x);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N;
    
    A.assign(N, 0);
    ST.assign(4*N, 0);
    lazy_assign.assign(4*N, 0);
    lazy_add.assign(4*N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int type, a, b;
    ll x;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> a >> b >> x;
            update_add(0, N-1, 0, a-1, b-1, x);
        } else if (type == 2) {
            cin >> a >> b >> x;
            update_assign(0, N-1, 0, a-1, b-1, x);
        } else {
            cin >> a >> b;
            ll val = query(0, N-1, 0, a-1, b-1);
            cout << val << endl;
        }
    }
    
    return 0;
}