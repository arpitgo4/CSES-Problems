// Salary Queries (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
/**
 * With Segment tree implementation we can't control the query's
 * time complexity. Worst case can be O(NlogN) per query rather than
 * O(logN)
 */

vector<int> A, ST_min, ST_max;

void build_seg_tree(int l, int h, int i) {
    if (l == h) {
        ST_min[i] = ST_max[i] = A[l];
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    ST_max[i] = max(ST_max[2*i+1], ST_max[2*i+2]);
    ST_min[i] = min(ST_min[2*i+1], ST_min[2*i+2]);
}

int query(int l, int h, int i, int a, int b) {
    if (l == h)
        return (a <= ST_max[i] && ST_max[i] <= b) ? 1 : 0;          // can be either of the seg trees, as the value of inidivual element will remain same
    if (ST_max[i] < a || ST_min[i] > b)
        return 0;
    if (a <= ST_min[i] && ST_max[i] <= b)
        return h-l+1;

    int count = 0;

    int m = (h-l)/2 + l;
    count += query(l, m, 2*i+1, a, b);
    count += query(m+1, h, 2*i+2, a, b);
    
    return count;
}

void update(int l, int h, int i, int k, int x) {
    if (l == h && l == k) {
        ST_max[i] = ST_min[i] = A[l] = x;
        return;
    }

    int m = (h-l)/2 + l;
    if (k <= m)
        update(l, m, 2*i+1, k, x);
    else update(m+1, h, 2*i+2, k, x);

    ST_max[i] = max(ST_max[2*i+1], ST_max[2*i+2]);
    ST_min[i] = min(ST_min[2*i+1], ST_min[2*i+2]);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;
    
    A.assign(N, 0);
    ST_max.assign(4*N, 0);
    ST_min.assign(4*N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    char c;
    int a, b, k, x;
    for (int i = 0; i < Q; i++) {
        cin >> c;
        if (c == '!') {
            cin >> k >> x;
            update(0, N-1, 0, k-1, x);
        } else {
            cin >> a >> b;
            int count = query(0, N-1, 0, min(a,b), max(a,b));
            cout << count << endl;
        }
    }
    
    return 0;
}