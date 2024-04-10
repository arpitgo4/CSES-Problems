// Range Update Queries (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
 
// Time: O(N + QlogN)               // N: build segment tree & diff array, QlogN: all queries
// Space: O(N)
 
/**
 * TODO: implement `update()` iteratively.
 * Recursive impl. is giving TLE
*/

typedef long long ll;

int N;
vector<ll> A, D, seg_tree;
 
void print_vector(vector<ll>& A) {
    for (int a : A)
        cout << a << " ";
    cout << endl;
}

ll query(int l, int h, int i, int p, int q) {
    if (p > q)
        return 0;
    if (l == h)
        return seg_tree[i];

    int m = (h-l)/2 + l;
    return query(l, m, 2*i+1, p, min(m, q)) +
            query(m+1, h, 2*i+2, max(m+1, p), q);
}

void update(int l, int h, int i, int idx, int val) {
    if (idx >= N)
        return;
    if (l == h && l == idx) {
        seg_tree[i] += val;
        D[idx] += val;
        return;
    }

    int m = (h-l)/2 + l;
    if (idx <= m)
        update(l, m, 2*i+1, idx, val);
    else update(m+1, h, 2*i+2, idx, val);

    seg_tree[i] = seg_tree[2*i+1] + seg_tree[2*i+2];
}

void build_seg_tree(int l, int h, int i) {
    if (l == h) {
        seg_tree[i] = D[l];
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    seg_tree[i] = seg_tree[2*i+1] + seg_tree[2*i+2];
}

void build_difference_array() {
    D[0] = A[0];
    for (int i = 1; i < N; i++)
        D[i] = A[i] - A[i-1];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    cin >> N >> Q;

    A.assign(N, 0);
    D.assign(N, 0);
    seg_tree.assign(4*N, 0);

    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_difference_array();
    build_seg_tree(0, N-1, 0);

    int type, l, h, val, k;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> l >> h >> val;
            update(0, N-1, 0, l-1, val);
            update(0, N-1, 0, h, -val);
        } else {
            cin >> k;
            cout << query(0, N-1, 0, 0, k-1) << endl;
        }
    }
    
    return 0;
}