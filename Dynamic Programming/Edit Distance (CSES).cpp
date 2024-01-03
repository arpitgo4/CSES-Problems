// Edit Distance (CSES)

#include <iostream>

using namespace std;

// Time: O(N*M)
// Space: O(N*M)

////////////////////////////////////////////////////////////////////////////////////////////////

void solve_iterative(string& A, string& B) {
    int n = A.length(), m = B.length();
    int N = max(n, m);
    vector<vector<int>> dp(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; i++) {
        if (A[i] != B[0])
            dp[i][0] = 1;
        if (A[0] != B[i])
            dp[0][i] = 1;
    }

    // TODO: we need to cover the case where one of the string is longer than the other
    // in that case, first two if cases from recursive implementation have to applied
    // create dp metrix with max(N, M) and last 

    // add => 1 + (i, j-1)
    // remove => 1 + (i-1, j)
    // replace => 1 + (i-1, j-1)

    //   M O V I E
    // L 1 1 1 1 1
    // O 1 1 2 2 2
    // V 1 2 1 2 3
    // E 1 2 2 2 2 <= min edit distance
    
    // (1,1) => (OVIE, OVE)
    //          => (1, 0) => (O, M) => 1 (add)
    //          => (0, 1) => (L, O) => 1 (remove)
    //          => (1, 1) => (O, O) => 0 (replace)

    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++) {
            if (i >= n)
                dp[i][j] = dp[i-1][j-1] + m-j;
            if (j >= m)
                dp[i][j] = dp[i-1][j-1] + n-i;
            if (A[i] == B[j])
                dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({ dp[i][j-1], dp[i-1][j], dp[i-1][j-1] });
        }

    cout << dp[N-1][N-1];
}

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int>> cache;

int dfs(int i, int j, string& A, string& B, int N, int M) { 
    if (i == N)
        return M-j;
    if (j == M)
        return N-i;
    if (cache[i][j] != -1)
        return cache[i][j];
    
    if (A[i] == B[j])
        return dfs(i+1, j+1, A, B, N, M);

    int add_op = 1 + dfs(i, j+1, A, B, N, M);
    int remove_op = 1 + dfs(i+1, j, A, B, N, M);
    int replace_op = 1 + dfs(i+1, j+1, A, B, N, M);

    return cache[i][j] = min({ add_op, remove_op, replace_op });
}

void solve_recursive(string& A, string& B) {
    int N = A.length(), M = B.length();
    cache.assign(N, vector<int>(M, -1));
    int count = dfs(0, 0, A, B, N, M);
    cout << count;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string A, B;
    cin >> A >> B;

    // solve_recursive(A, B);
    solve_iterative(A, B);

    return 0;
}