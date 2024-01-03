// Grid Paths (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N^2)
// Space: O(N^2)

//////////////////////////////////////////////////////////////////////////////////////////

const int MOD = 1e9 + 7;
vector<vector<int>> dp;

void solve_iterative(vector<vector<char>>& A, int N) {
    dp.assign(N, vector<int>(N, 0));
    if (A[0][0] != '*')
        dp[0][0] = 1;

    // recurrence relation: dp[i][j] = dp[i-1][j] + dp[i][j-1]

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0)
                continue;
            if (A[i][j] != '*') {
                int a = i-1 >= 0 ? dp[i-1][j] : 0;
                int b = j-1 >= 0 ? dp[i][j-1] : 0;
                dp[i][j] = (a + b) % MOD;
            }
        }

    cout << dp[N-1][N-1];
}

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int>> cache;

int dfs(int i, int j, vector<vector<char>>& A, int N) {
    if (i == N || j == N || A[i][j] == '*')
        return 0;
    if (i == N-1 && j == N-1)
        return 1;
    if (cache[i][j] != -1)
        return cache[i][j];

    return cache[i][j] = (dfs(i+1, j, A, N) + dfs(i, j+1, A, N)) % MOD;
}

void solve_recursive(vector<vector<char>>& A, int N) {
    cache.assign(N, vector<int>(N, -1));
    cout << dfs(0, 0, A, N);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<vector<char>> A(N, vector<char>(N, '.'));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    // solve_recursive(A, N);
    solve_iterative(A, N);

    return 0;
}