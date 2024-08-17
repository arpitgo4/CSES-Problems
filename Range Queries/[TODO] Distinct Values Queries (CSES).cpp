// Distinct Values Queries (CSES)
 
#include <iostream>
#include <vector>
#include <unordered_set>
 
using namespace std;

/**
 * Can't use Small-Large Merge heuristic here
 * 
 * Because when we merge two sets into one, larger of the
 * two sets gets has all values of both and parent node
 * starts referencing it. But, the node that had the larger set
 * previously now have the merged set and represents that for its 
 * subtree, which is incorrect.
 * 
 * This heuristic can be used to one time processing on the tree but
 * not for subsequent queries.
 * 
 * We need MO's algorithm here!
 */

// Time: O(NlogN + QlogN) ~ O((N + Q)logN)
// Space: O(N)

vector<int> A;
vector<unordered_set<int>> ST;

// small to large merging heuristic
int merge(int a, int b) {
    if (ST[a].size() < ST[b].size())
        swap(a, b);

    for (int v : ST[b])
        ST[a].insert(v);

    return a;
}

int query(int l, int h, int i, int a, int b) {
    if (l == h || (l == a && h == b))
        return ST[i].size();
    
    int count = 0;

    int m = (h-l)/2 + l;
    count += query(l, m, 2*i+1, a, min(m, b));
    count += query(m+1, h, 2*i+2, max(m+1, a), b);

    return count;
}

void build_seg_tree(int l, int h, int i) {
    if (l == h) {
        ST[i] = *new unordered_set<int>{ A[l] };
        return;
    }

    int m = (h-l)/2 + l;
    build_seg_tree(l, m, 2*i+1);
    build_seg_tree(m+1, h, 2*i+2);

    int max_idx = merge(2*i+1, 2*i+2);
    ST[i] = ST[max_idx];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;
    
    A.assign(N, 0);
    ST.resize(4*N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    char c;
    int a, b, k, x;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        int count = query(0, N-1, 0, a-1, b-1);
        cout << count << endl;
    }
    
    return 0;
}