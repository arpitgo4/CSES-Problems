// Planets Queries I (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
 
// Time: O(NlogN + QlogN)
// Space: O(NlogN)

const int max_k = 1e9;
vector<vector<int>> sparse_table;

void print_vector(vector<vector<int>>& A) {
    for (auto& v : A) {
        for (int a : v)
            cout << a << " ";
        cout << endl;
    }
}

void build_sparse_table(vector<int>& par, int N) {
    int max_pow = ceil(log2(max_k));
    sparse_table.assign(max_pow + 1, vector<int>(N+1, -1));

    for (int i = 1; i < N+1; i++)
        sparse_table[0][i] = par[i-1];

    for (int pow = 1; pow <= max_pow; pow++)
        for (int i = 1; i < N+1; i++)
            sparse_table[pow][i] = sparse_table[pow-1][sparse_table[pow-1][i]];
}

int query(int u, int k) {
    if (k == 0)
        return u;

    int pow = log2(k);
    return query(sparse_table[pow][u], k-(1 << pow));
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;

    vector<int> par(N);
    for (int i = 0; i < N; i++)
        cin >> par[i];

    build_sparse_table(par, N);

    int u, k;
    for (int i = 0; i < Q; i++) {
        cin >> u >> k;
        cout << query(u, k) << endl;
    }
    
    return 0;
}