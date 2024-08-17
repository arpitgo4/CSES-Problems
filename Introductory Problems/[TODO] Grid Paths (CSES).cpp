// Grid Paths (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N^2)
// Space: O(N^2)
 
const int MAX_N = 7;

vector<vector<vector<int>>> dp;
vector<vector<int>> vis;

vector<pair<int,int>> dir{
    { -1, 0 },              // up
    { 1, 0 },               // down
    { 0, -1 },              // left
    { 0, 1 }                // right
};

int dfs(int i, int j, string& S, int move_idx) {
    if (i < 0 || i == MAX_N || j < 0 || j == MAX_N || move_idx > 48) //  || vis[i][j] != 0
        return 0;
    if (i == MAX_N-1 && j == 0 && move_idx == 48)
        return 1;
    if (dp[i][j][move_idx] != -1)
        return dp[i][j][move_idx];

    // vis[i][j] = 1;

    int count = 0;
    if (S[move_idx] == 'U')
        count = dfs(i-1, j, S, move_idx+1);
    else if (S[move_idx] == 'D')
        count = dfs(i+1, j, S, move_idx+1);
    else if (S[move_idx] == 'L')
        count = dfs(i, j-1, S, move_idx+1);
    else if (S[move_idx] == 'R')
        count = dfs(i, j+1, S, move_idx+1);
    else {
        for (auto& [di, dj] : dir) {
            count += dfs(i+di, j+dj, S, move_idx+1);
        }
    }

    return dp[i][j][move_idx] = count;
}

void solve(string& S) {
    dp.assign(MAX_N, vector<vector<int>>(MAX_N, vector<int>(MAX_N * MAX_N, -1)));
    vis.assign(MAX_N, vector<int>(MAX_N, 0));

    int count = dfs(0, 0, S, 0);

    cout << count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);
    
    return 0;
}