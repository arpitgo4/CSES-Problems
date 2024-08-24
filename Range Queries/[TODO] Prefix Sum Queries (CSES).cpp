// Prefix Sum Queries (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
/**
 * Let's say for building 0,
 * every building on the right will get 1,2,3....N-1
 * added to their pizza price and we need to find the
 * minimum out all final prices.
 * 
 * For building i,
 * every building on the left of i will get i-1...3,2,1 and
 * on the right will get 1,2,3...N-i-1 added and we need to 
 * find the minimum out of it.
 * 
 * Range Updates & Range Minimums with Segment Tree can be useful here!
 */

#define INF LLONG_MAX

typedef long long ll;

vector<ll> A, ST;
 
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

    ST[i] = min(ST[2*i+1], ST[2*i+2]);
}

ll query(int l, int h, int i, int k) {
    if (l > h)
        return;
    if (l == h && l == k) {

    }

    int m = (h-l)/2 + l;

    return -1;
}

void update(int l, int h, int i, int k, ll x) {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;
    
    A.assign(N, 0);
    ST.assign(4*N, INF);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int type, k;
    ll x;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> k >> x;
            update(0, N-1, 0, k, x);
        } else {
            cin >> k;
            ll price = query(0, N-1, 0, k-1);
            cout << price << endl;
        }
    }
    
    return 0;
}