// Grid Paths (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N * N)
// Space: O(N * N)

typedef pair<int,int> pos;

const int MOD = 1e9 + 7;
 
vector<vector<int>> G;
vector<vector<int>> dp;

int dfs(int i, int j, int N) {
    if (i < 0 || i == N || j < 0 || j == N || G[i][j] == 1)
        return 0;
    if (i == N-1 && j == N-1)
        return 1;
    if (dp[i][j] != -1)
        return dp[i][j];

    int count = (dfs(i+1, j, N) % MOD + dfs(i, j+1, N) % MOD) % MOD;

    return dp[i][j] = count;
}

void solve(vector<pos>& traps, int N, int M) {
    G.assign(N+1, vector<int>(N+1, 0));
    dp.assign(N+1, vector<int>(N+1, -1));
    for (pos& p : traps) {
        int i = p.first, j = p.second;
        G[i-1][j-1] = 1;
    }

    int count = dfs(0, 0, N);
    cout << count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;

    int i, j;
    vector<pos> traps(M);
    for (int k = 0; k < M; k++) {
        cin >> i >> j;
        traps[k] = { i, j };
    }

    solve(traps, N, M);
    
    return 0;
}