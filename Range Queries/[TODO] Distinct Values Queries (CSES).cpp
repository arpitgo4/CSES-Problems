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

// Time: O(N + Q√N)
// Space: O(√N)

const int MAX_N = 2e5;
const int BLK_CNT = (int) sqrt(MAX_N + .0) + 1;

vector<unordered_set<int>> B;

void build_blocks(vector<int>& A, int N) {
    B.assign(BLK_CNT, unordered_set<int>());
    for (int i = 0; i < N; i++)
        B[i/BLK_CNT].insert(A[i]);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;
    
    vector<int> A(N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_blocks(A, N);

    int a, b;
    vector<int> q_idx(Q);
    vector<pair<int,int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        q_idx[i] = i;
        cin >> a >> b;
        queries[i] = { a, b };
    }

    sort(q_idx.begin(), q_idx.end(), [&](const int a, const int b) {
        if (queries[a].first == queries[b].first)
            return queries[a].second > queries[b].second;

        return queries[a].first < queries[b].first;
    });

    vector<int> res(Q);
    for (int i = 0; i < Q; i++) {
        int idx = q_idx[i];
        auto& [l, h] = queries[idx];

        
    }

    for (int r : res)
        cout << r << endl;
    
    return 0;
}