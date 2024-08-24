// Range Xor Queries (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N + QlogN)
// Space: O(N)

/**
 * We don't need updates, hence we don't have to use Segment Trees
 * 
 * Prefix Query data structure should be enough for this problem!
 * 
 * Because Segment tree was already implemented, went ahead with it only.
 * 
 * TODO: Use Prefix data structure for better query time complexity i.e. O(1)
 */

vector<int> ST, A;

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

    ST[i] = ST[2*i+1] ^ ST[2*i+2];
}

int query(int l, int h, int i, int p, int q) {
    if (l > h || p > q)
        return 0;
    if (l == p && h == q)
        return ST[i];
    
    int m = (h-l)/2 + l;
    int a = query(l, m, 2*i+1, p, min(q, m));
    int b = query(m+1, h, 2*i+2, max(m+1, p), q);

    return a ^ b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    A.assign(N, 0);
    ST.assign(4*N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        int val = query(0, N-1, 0, a-1, b-1);
        cout << val << endl;
    }

    return 0;
}