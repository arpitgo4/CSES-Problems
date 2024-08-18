// Hotel Queries (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
/**
 * You always assign a group to the first hotel having enough rooms.
 */

vector<int> ST, A;

void build_seg_tree(int l, int h, int i) {
    if (l == h) {
        ST[i] = A[l];
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    ST[i] = max(ST[2*i+1], ST[2*i+2]);
}

void update(int l, int h, int i, int k, int x) {
    if (l == h && l == k) {
        ST[i] = A[l] = x;
        return;
    }

    int m = (h-l)/2 + l;
    if (k <= m)
        update(l, m, 2*i+1, k, x);
    else update(m+1, h, 2*i+2, k, x);

    ST[i] = max(ST[2*i+1], ST[2*i+2]);
}

int query(int l, int h, int i, int q) {
    if (l == h)
        return (ST[i] >= q ? l : -1);
        
    int m = (h-l)/2 + l;
    if (q <= ST[2*i+1])
        return query(l, m, 2*i+1, q);
    else return query(m+1, h, 2*i+2, q);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    
    A.assign(N, 0);
    ST.assign(4*N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int q;
    for (int i = 0; i < M; i++) {
        cin >> q;
        int idx = query(0, N-1, 0, q);
        cout << (idx+1) << " ";

        if (idx != -1)
            update(0, N-1, 0, idx, A[idx]-q);
    }
    cout << endl;
    
    return 0;
}