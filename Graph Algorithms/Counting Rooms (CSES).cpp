// Counting Rooms (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

// Time: O(N * M)
// Space: O(N * M)

vector<vector<int>> V;

void dfs(vector<vector<char>>& G, int i, int j, int N, int M) {
    if (i < 0 || j < 0 || i == N || j == M || V[i][j] == 1 || G[i][j] == '#')
        return;

    V[i][j] = 1;

    dfs(G, i, j+1, N, M);   // right
    dfs(G, i, j-1, N, M);   // left
    dfs(G, i+1, j, N, M);   // up
    dfs(G, i-1, j, N, M);   // down
}

void solve(vector<vector<char>>& G, int N, int M) {
    V.assign(N, vector<int>(M, 0));
    int counter = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (V[i][j] == 0 && G[i][j] == '.') {
                dfs(G, i, j, N, M);
                counter++;
            }

    cout << counter;
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
