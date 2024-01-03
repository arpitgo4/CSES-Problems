// Throwing Dice (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;

// Time: O(K^3 * logN) ~ O(6^3 * logN) ~ O(logN)
// Space: O(K^2) ~ O(1)

const ll MOD = 1e9 + 7;

vector<vector<ll>> multiply_matrix(vector<vector<ll>>& A, vector<vector<ll>>& B) {
    int N = A.size();
    int M = A[0].size();
    int P = B[0].size();

    vector<vector<ll>> res(N, vector<ll>(P, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++)
            for (int k = 0; k < M; k++)
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;

    return res;
}

vector<vector<ll>> matrix_exponentiation(vector<vector<ll>>& mat, ll p) {
    vector<vector<ll>> res(6, vector<ll>(6, 0));
    for (int i = 0; i < 6; i++)
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
 
void solve(ll N) {
    vector<vector<ll>> X(6, vector<ll>(6, 0));
    for (int i = 0; i < 6; i++)
        X[0][i] = 1;
    for (int i = 0; i < 5; i++)
        X[i+1][i] = 1;

    vector<vector<ll>> Y{
        {16}, {8}, {4}, {2}, {1}, {1}
    };

    vector<vector<ll>> mat_exp = matrix_exponentiation(X, N);
    vector<vector<ll>> res = multiply_matrix(mat_exp, Y);

    cout << res[5][0];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N;
    cin >> N;

    solve(N);
    
    return 0;
}