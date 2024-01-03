// Graph Paths II (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <tuple>
 
using namespace std;
using ll = long long;
 
// Time: O(V^3 * logK)
// Space: O(V^2)

vector<vector<ll>> G;

vector<vector<ll>> min_multiply_matrix(vector<vector<ll>>& A, vector<vector<ll>>& B) {
    int N = A.size();
    vector<vector<ll>> res(N, vector<ll>(N, LLONG_MAX));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                if (A[i][k] != LLONG_MAX && B[k][j] != LLONG_MAX)
                    res[i][j] = min(res[i][j], A[i][k] + B[k][j]);

    return res;
}

vector<vector<ll>> matrix_exponentiation(vector<vector<ll>>& mat, ll p) {
    int N = mat.size();
    vector<vector<ll>> res(N, vector<ll>(N, LLONG_MAX));
    for (int i = 0; i < N; i++)
        res[i][i] = 0;

    while (p > 0) {
        if (p % 2 == 1) {
            res = min_multiply_matrix(res, mat);
            p--;
        }

        mat = min_multiply_matrix(mat, mat);
        p >>= 1;
    }

    return res;
}

void solve(int V, int E, int K, vector<tuple<int,int,ll>>& edges) {
    G.assign(V, vector<ll>(V, LLONG_MAX));
    for (tuple<int,int,ll>& e : edges) {
        int u, v; ll w;
        tie(u,v,w) = e;
        G[u-1][v-1] = min(G[u-1][v-1], w);
    }

    vector<vector<ll>> res = matrix_exponentiation(G, K);
    ll path_length = res[0][V-1];
    cout << (path_length == LLONG_MAX ? -1 : path_length);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E, K;
    cin >> V >> E >> K;

    int u, v; ll w;
    vector<tuple<int,int,ll>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };    
    }

    solve(V, E, K, edges);
    
    return 0;
}