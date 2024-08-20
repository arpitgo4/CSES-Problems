// List Removals (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N + NlogN)
// Space: O(N)
 
vector<int> ST, A;

void build_seg_tree(int l, int h, int i) {
    if (l > h)
        return;
    if (l == h) {
        ST[i] = 1;
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

int query(int l, int h, int i, int k) {
    if (l == h) {
        ST[i] = 0;
        return A[l];
    }

    int m = (h-l)/2 + l;
    int val = 0;
    if (k <= ST[2*i+1])
        val = query(l, m, 2*i+1, k);
    else val = query(m+1, h, 2*i+2, k-ST[2*i+1]);

    ST[i] = ST[2*i+1] + ST[2*i+2];

    return val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    A.assign(N, 0);
    ST.assign(4*N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int q;
    for (int i = 0; i < N; i++) {
        cin >> q;
        int val = query(0, N-1, 0, q);
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}