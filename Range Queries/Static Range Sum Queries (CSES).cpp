// Static Range Sum Queries (CSES)

// NOTE: Had to convert vector<int> A to vector<long long> A even though input range is <= 1e9
// Maybe, adding two integers and then storing it in long long is causing number overflow in the addition
// step only

// Improvements idea,
// 1. Use Sparse Segment Tree, i.e. avoid building segment tree as whole, only build paths when queried. This approach significantly saves time by avoiding build tree routine and memory will be allocated only based on the query paths which are required for processing.

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// range sum segment tree
class SegmentTree {
public:
    SegmentTree(vector<long long>& OA) {
        A = OA;
        N = A.size();
        ST.assign(4*N, 0);
        build(ST, A, 0, N-1, 0);
    }

    long long query(int l, int h) {
        return query(0, N-1, 0, l, h);
    }
private:

    int N;
    vector<long long> A;
    vector<long long> ST;

    // Time: O(4*N) ~ O(N)
    // Space: O(4*N) ~ O(N)
    long long build(vector<long long>& ST, vector<long long>& A, int l, int h, int i) {
        if (l > h)
            return 0;
        if (l == h)
            return ST[i] = A[l];

        int m = (h-l)/2 + l;
        ST[i] = build(ST, A, l, m, 2*i+1) + build(ST, A, m+1, h, 2*i+2);

        return ST[i];
    }

    // Time: O(logN)
    // Space: O(logN)
    long long query(int l, int h, int i, int p, int q) {
        if (l > h)
            return 0;
        if (l == h || (l == p && h == q))
            return ST[i];
        
        int m = (h-l)/2 + l;
        if (p <= m && q <= m)
            return query(l, m, 2*i+1, p, q);
        else if (p > m && q > m)
            return query(m+1, h, 2*i+2, p, q);
        
        return query(l, m, 2*i+1, p, m) + query(m+1, h, 2*i+2, m+1, q);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<long long> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    SegmentTree ST(A);

    vector<pair<int,int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        queries[i] = { a, b };
    }

    for (int i = 0; i < Q; i++)
        cout << ST.query(queries[i].first-1, queries[i].second-1) << endl;

    return 0;
}