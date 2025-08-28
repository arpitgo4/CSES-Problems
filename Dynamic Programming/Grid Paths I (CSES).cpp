// Grid Paths I (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N^2)
// Space: O(N^2)

using grid_t = vector<vector<int>>;
 
const int MOD = 1e9 + 7;

int countPaths(
    int curr_i,
    int curr_j,
    grid_t& grid,
    int grid_sz,
    grid_t& dp
) {
    if (curr_i == grid_sz || curr_j == grid_sz || grid[curr_i][curr_j] == 1)
        return 0;
    if (curr_i == grid_sz-1 && curr_j == grid_sz-1)
        return 1;
    if (dp[curr_i][curr_j] != -1)
        return dp[curr_i][curr_j];
    
    int down_path_cnt = countPaths(
        curr_i+1,
        curr_j,
        grid,
        grid_sz,
        dp
    );

    int right_path_cnt = countPaths(
        curr_i,
        curr_j+1,
        grid,
        grid_sz,
        dp
    );

    return dp[curr_i][curr_j] = (
        (down_path_cnt + right_path_cnt) % MOD
    );
}

void solve(
    grid_t& grid,
    int grid_sz
) {
    grid_t dp(grid_sz, vector<int>(grid_sz, -1));
    int path_cnt = countPaths(
        0,
        0,
        grid,
        grid_sz,
        dp
    );

    cout << path_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int grid_sz;
    cin >> grid_sz;

    char ch;
    grid_t grid(grid_sz, vector<int>(grid_sz, 0));
    for (int i = 0; i < grid_sz; i++) {
        for (int j = 0; j < grid_sz; j++) {
            cin >> ch;
            if (ch == '*')
                grid[i][j] = 1;
        }
    }

    solve(
        grid,
        grid_sz
    );
    
    return 0;
}