// Company Queries I (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;

// Pre-processing Time: O(NlogN)
// Time per query: O(logN)
// Total time: O(NlogN + QlogN)
// Space: O(NlogN)

const int MAX_N = 2 * 1e5 + 1;
vector<int> P(MAX_N, -1);
vector<vector<int>> sparse_table(log2(MAX_N) + 1, vector<int>(MAX_N, -1));

// binary-lifting on trees
void build_sparse_table(int N) {
    int max_pow = log2(N);

    // 2^0 ~ (1 << 0)
    for (int i = 2; i < N+1; i++)
        sparse_table[0][i] = P[i];

    for (int pow = 1; pow < max_pow+1; pow++) {
        for (int i = 2; i < N+1; i++) {
            int par = sparse_table[pow-1][i];
            if (par != -1)
                sparse_table[pow][i] = sparse_table[pow-1][par];
        }
    }
}

int query_sparse_table(int u, int k) {
    if (k == 0 || u == -1)
        return u;
    
    int pow = log2(k);
    return query_sparse_table(sparse_table[pow][u], k - (1 << pow));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;

    int p;
    for (int i = 2; i < N+1; i++) {
        cin >> p;
        P[i] = p;
    }

    build_sparse_table(N);

    int u, k;
    for (int i = 0; i < Q; i++) {
        cin >> u >> k;
        cout << query_sparse_table(u, k) << endl;
    }
    
    return 0;
}