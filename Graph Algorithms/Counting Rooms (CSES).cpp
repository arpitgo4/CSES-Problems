// Counting Rooms (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N * M)
// Space: O(N * M)
 
vector<vector<int>> vis;

void dfs(int i, int j, vector<vector<char>>& A, int N, int M) {
    if (i < 0 || i == N || j < 0 || j == M || A[i][j] == '#' || vis[i][j] != 0)
        return;

    vis[i][j] = 1;

    dfs(i-1, j, A, N, M);
    dfs(i+1, j, A, N, M);
    dfs(i, j-1, A, N, M);
    dfs(i, j+1, A, N, M);

    vis[i][j] = 2;
}

void solve(vector<vector<char>>& A, int N, int M) {
    vis.assign(N, vector<int>(M, 0));

    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            if (vis[i][j] == 0 && A[i][j] == '.') {
                dfs(i, j, A, N, M);
                count++;
            }
        }

    cout << count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;

    vector<vector<char>> A(N, vector<char>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> A[i][j];

    solve(A, N, M);
    
    return 0;
}
