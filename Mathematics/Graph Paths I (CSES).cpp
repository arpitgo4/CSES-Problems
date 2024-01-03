// Graph Paths I (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
using ll = long long;
 
// Time: O(V^3 * logK)
// Space: O(V^2)

const ll MOD = 1e9 + 7;
vector<vector<ll>> G;

vector<vector<ll>> multiply_matrix(vector<vector<ll>>& A, vector<vector<ll>>& B) {
    int N = A.size();
    vector<vector<ll>> res(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;

    return res;
}

vector<vector<ll>> matrix_exponentiation(vector<vector<ll>> mat, ll p) {
    int N = mat.size();
    vector<vector<ll>> res(N, vector<ll>(N, 0));          // identity matrix
    for (int i = 0; i < N; i++)
        res[i][i] = 1;

    while (p > 0) {
        if (p % 2 == 1) {
            res = multiply_matrix(res, mat);
            p--;
        }

        mat = multiply_matrix(mat, mat);
        p >>= 1;
    }

    return res;
}

void solve(int V, int E, int K, vector<pair<int,int>>& edges) {
    G.assign(V, vector<ll>(V, 0));
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u-1][v-1]++;                              // count of edges between u and v
    }

    vector<vector<ll>> res = matrix_exponentiation(G, K);
    cout << res[0][V-1];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E, K;
    cin >> V >> E >> K;

    int u, v;
    vector<pair<int,int>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };    
    }

    solve(V, E, K, edges);
    
    return 0;
}