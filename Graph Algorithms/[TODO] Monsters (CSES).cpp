// Monsters (CSES)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// INTUITION: BFS with Bracktracking to explore all the possible escape routes
// Target all possible escape options. Explore all (shortest, duh! we are using BFS) possible escape route to an option
// Assuming while exploring an escape route Monsters already know about it and trying to,
    // either get in my way and catch from front
    // or following me to catch me from behind ---- think for edge cases!!!!

vector<int> VIS;

void bfs(vector<vector<int>>& A, int s_i, int s_j) {
    queue<int> q;
    q.push(source);

    while (!q.empty()) {

    }
}

void solve(vector<vector<int>>& A) {
    int N = A.size();
    int M = A[0].size();

    VIS.assign(N, vector<int>(M, 0));

    int s_i = -1, s_j = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == 'A') {
                s_i = i;
                s_j = j;
                break;
            }
        }
        if (s_i != -1 && s_j != -1)
            break;
    }

    bfs(A, s_i, s_j);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<vector<char>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> A[i][j];

    solve(A);

    return 0;
}