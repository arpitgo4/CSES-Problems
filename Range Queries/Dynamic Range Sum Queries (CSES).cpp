// Dynamic Range Sum Queries (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

class SegmentTree {
private:
    int N;
    vector<ll> A;
    vector<ll> ST;

    ll build(int l, int h, int i) {
        if (l > h)
            return 0;
        if (l == h)
            return ST[i] = A[l];
        
        int m = (h-l)/2 + l;
        return ST[i] = build(l, m, 2*i+1) + build(m+1, h, 2*i+2);
    }

    ll _query(int l, int h, int i, int  p, int q) {
        if (l > h)
            return 0;
        if (l == p && h == q)
            return ST[i];

        int m = (h-l)/2 + l;
        if (p <= m && q <= m)
            return _query(l, m, 2*i+1, p, q);
        else if (p > m && q > m)
            return _query(m+1, h, 2*i+2, p, q);

        return _query(l, m, 2*i+1, p, m) + _query(m+1, h, 2*i+2, m+1, q);
    }

    ll _update(int l, int h, int i, int idx, int val) {
        if (l > h)
            return 0;
        if (l == h && l == idx)
            return ST[i] = A[l] = val;

        int m = (h-l)/2 + l;
        if (idx <= m) {
            ll updated_val = _update(l, m, 2*i+1, idx, val);
            return ST[i] = updated_val + ST[2*i+2];
        }
        else {
            ll updated_val = _update(m+1, h, 2*i+2, idx, val);
            return ST[i] = ST[2*i+1] + updated_val;
        }
    }
public:
    SegmentTree(vector<ll>& OA) {
        A = OA;
        N = A.size();
        ST.assign(4*N, 0);
        build(0, N-1, 0);
    }

    ll query(int l, int h) {
        return _query(0, N-1, 0, l, h);
    }

    ll update(int idx, int val) {
        return _update(0, N-1, 0, idx, val);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    SegmentTree sg(A);

    vector<ll> res;
    int type, a, b;
    for (int i = 0; i < Q; i++) {
        cin >> type >> a >> b;        
        if (type == 1)
            sg.update(a-1, b);
        else 
            res.push_back(sg.query(a-1, b-1));
    }

    for (ll a : res)
        cout << a << endl;

    return 0;
}