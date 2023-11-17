// Dynamic Range Minimum Queries (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class SegmentTree {
private:

    vector<int> ST;
    vector<int> A;
    int N;

    int build(int l, int h, int i) {
        if (l > h)
            return INT_MAX;
        if (l == h)
            return ST[i] = A[l];

        int m = (h-l)/2 + l;
        int a = build(l, m, 2*i+1);
        int b = build(m+1, h, 2*i+2);

        return ST[i] = min(a, b);
    }

    int query(int l, int h, int i, int p, int q) {
        if (l > h)
            return INT_MAX;
        if (l == p && h == q)
            return ST[i];
        
        int m = (h-l)/2 + l;
        if (m >= q && m >= p)
            return query(l, m, 2*i+1, p, q);
        else if (q > m && p > m)
            return query(m+1, h, 2*i+2, p, q);

        return min(
            query(l, m, 2*i+1, p, m),
            query(m+1, h, 2*i+2, m+1, q)
        );
    }

    int update(int l, int h, int i, int idx, int val) {
        if (l > h)
            return INT_MAX;
        if (l == idx && l == h)
            return ST[i] = A[idx] = val;

        int m = (h-l)/2 + l;
        if (idx <= m) {
            return ST[i] = min(
                update(l, m, 2*i+1, idx, val),
                ST[2*i+2]
            );
        } else {
            return ST[i] = min(
                ST[2*i+1],
                update(m+1, h, 2*i+2, idx, val)
            );
        }
    }

public:
    SegmentTree(vector<int>& oA, int n) {
        A = oA;
        N = n;
        ST.assign(4*N, INT_MAX);
        build(0, N-1, 0);
    }

    int query(int l, int h) {
        return query(0, N-1, 0, l, h);
    }

    int update(int idx, int val) {
        return update(0, N-1, 0, idx, val);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    SegmentTree sg(A, N);

    int t, a, b;
    for (int i = 0; i < Q; i++) {
        cin >> t >> a >> b;
        if (t == 1) {
            sg.update(a-1, b);
        } else {
            cout << sg.query(a-1, b-1) << endl;
        }
    }

    return 0;
}