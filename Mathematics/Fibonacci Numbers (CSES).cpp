// Fibonacci Numbers (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;
 
// Time: O(logN)
// Space: O(1)

const ll MOD = 1e9 + 7;

vector<vector<ll>> multiply_matrix(vector<vector<ll>>& A, vector<vector<ll>> B) {
    vector<vector<ll>> res(2, vector<ll>(2, 0));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;

    return res;
}

vector<vector<ll>> matrix_exponentiation(vector<vector<ll>>& mat, ll p) {
    vector<vector<ll>> res{                     // identity matrix
        {1, 0},
        {0, 1}
    };
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
    vector<vector<ll>> mat{
        { 1, 1 },
        { 1, 0 }
    };

    vector<vector<ll>> res = matrix_exponentiation(mat, N);
    cout << res[0][1];
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N;
    cin >> N;

    solve(N);
    
    return 0;
}