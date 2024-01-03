// Labyrinth (CSES)

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Time: O(N * M)
// Space: O(N * M)

// BFS traversal produces shortest path for non-weighted graphs

vector<vector<int>> V;
vector<vector<tuple<int,int,char>>> P;
vector<char> path;

void prepare_path(int i, int j) {
    int p_i, p_j;
    char move;
    tie(p_i, p_j, move) = P[i][j];

    while (p_i != -1 && p_j != -1) {
        path.push_back(move);
        tie(p_i, p_j, move) = P[p_i][p_j];
    }
}

bool bfs(vector<vector<char>>& G, int i, int j, int N, int M) {
    queue<tuple<int,int,char,int,int>> q;
    q.push({ i, j, 'N', -1, -1 });
    
    while (!q.empty()) {
        tuple<int,int,char,int,int> t = q.front();
        q.pop();

        int p_i, p_j, i, j;
        char move;
        tie(i, j, move, p_i, p_j) = t;

        if (i < 0 || i == N || j < 0 || j == M || V[i][j] == 1 || G[i][j] == '#')
            continue;

        P[i][j] = { p_i, p_j, move };
        V[i][j] = 1;

        if (G[i][j] == 'B') {
            prepare_path(i, j);
            return true;
        }

        q.push({ i, j-1, 'L', i, j });
        q.push({ i, j+1, 'R', i, j });
        q.push({ i-1, j, 'U', i, j });
        q.push({ i+1, j, 'D', i, j });
    }

    return false;
}

void solve(vector<vector<char>>& G, int N, int M) {
    V.assign(N, vector<int>(M, 0));
    P.assign(N, vector<tuple<int,int,char>>(M));

    bool path_found = false;
    int i = 0, j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (G[i][j] == 'A') break;
        }
        if (G[i][j] == 'A') break;
    }
    
    path_found = bfs(G, i, j, N, M);

    if (!path_found) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    cout << path.size() << endl;
    for (int i = path.size()-1; i >= 0; i--)
        cout << path[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<vector<char>> G(N, vector<char>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> G[i][j];

    solve(G, N, M);

    return 0;
}