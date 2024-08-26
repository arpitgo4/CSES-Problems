// Range Update Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
/**
 * Lazy propogation model,
 * 
 * For `update` call, target node is marked and new update value
 * is also updated at the target node. 
 * Since, update is not propogated at that time further down, 
 * this makes the range updates `O(logN)`.
 * But all the nodes (parents) above the target nodes are updated wit
 * new value on the way back.
 * 
 * For further `query` or `update` call, if a node has a marker lazy 
 * update is propogated further down the tree and new update values 
 * are also calculated for child nodes.
 * 
 * Above, optimization makes sure, we only propogate updates down the tree
 * step-by-step and only where we need to propogate. Otherwise, with eager
 * propogation time complexity will become `O(NlogN)`.
 * 
 * So to sum up, with lazy updates,
 * 1. Nodes above the target range update node have new updates values all 
 *    the time. Parent nodes can be queried and will provide correct results
 *    for there respective segments.
 * 2. Children nodes w.r.t. target node will have stale values till the time
 *    either `query` or `update` reaches to them. This is why before accessing
 *    the childrens' values we need to propogate the lazy update if there is.
 * 
 * `marked[i] == true`, marks the current node for lazy propogation before going
 * further down in it's subtree and `lazy[i]` denotes the value that is to be 
 * propogated.
 * 
 * With above in place, whenever I encounter any node in the segment tree, it's and 
 * it's parents' values are updated with all the lazy updates, which may or may not 
 * be the case of it's children.
 */

typedef long long ll;

vector<ll> ST, A, lazy;
vector<bool> marked;

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

void push(int l, int h, int i) {
    if (marked[i]) {
        int m = (h-l)/2 + l;

        // first update the new values in segment tree nodes with parent's lazy value
        ST[2*i+1] += lazy[i] * (m-l+1);
        ST[2*i+2] += lazy[i] * (h-m);

        // then, set the parent's lazy value which will be further propogated to children nodes
        lazy[2*i+1] += lazy[i];
        lazy[2*i+2] += lazy[i];
        marked[2*i+1] = marked[2*i+2] = true;

        lazy[i] = 0;
        marked[i] = false;
    }
}

void update(int l, int h, int i, int p, int q, ll x) {
    if (p > q)
        return;
    if (l == p && h == q) {
        /**
         * Here, if I update lazy[i] first and then use that to update ST[i],
         * 
         * lazy[i] += x;
         * ST[i] += lazy[i] * (h-l+1);
         * 
         * This is incorrect. As, whatever we had in lazy[p] was updated in ST[i]
         * and lazy[p] was propogated to ith node before reaching here, in the push(p) call.
         * 
         * Correct way is to,
         * ST[i] += x * (h-l+1);
         * lazy[i] += x;
         * 
         * Always update the current segment tree node with just the update value first and then
         * put the new update in the lazy[i].
         */
        ST[i] += x * (h-l+1);
        lazy[i] += x;
        marked[i] = true;
        return;
    }

    push(l, h, i);
    int m = (h-l)/2 + l;
    update(l, m, 2*i+1, p, min(q, m), x);
    update(m+1, h, 2*i+2, max(m+1, p), q, x);

    ST[i] = ST[2*i+1] + ST[2*i+2];
}

ll query(int l, int h, int i, int k) {
    if (l == h && l == k)
        return ST[i];
    
    push(l, h, i);
    int m = (h-l)/2 + l;
    if (k <= m)
        return query(l, m, 2*i+1, k);
    else return query(m+1, h, 2*i+2, k);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    
    A.assign(N, 0);
    ST.assign(4*N, 0);
    lazy.assign(4*N, 0);
    marked.assign(4*N, false);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int type, l, h, k;
    ll x;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> l >> h >> x;
            update(0, N-1, 0, l-1, h-1, x);
        } else {
            cin >> k;
            ll val = query(0, N-1, 0, k-1);
            cout << val << endl;
        }
    }
    
    return 0;
}