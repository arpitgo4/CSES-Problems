// Counting Rooms (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N * M)
// Space: O(N * M)
 
vector<pair<int,int>> moves {
    { -1, 0 },              // up
    { 1, 0 },               // down
    { 0, -1 },              // left
    { 0, 1 }                // right
};

void exploreRoom(
    int curr_i,
    int curr_j,
    vector<vector<int>>& chart,
    int chart_height,
    int chart_width,
    vector<vector<int>>& vis
) {
    if (curr_i < 0 || 
            curr_i == chart_height ||
            curr_j < 0 ||
            curr_j == chart_width || 
            chart[curr_i][curr_j] == 1 || 
            vis[curr_i][curr_j] == 1) {
        return;
    }

    vis[curr_i][curr_j] = 1;

    for (auto& move : moves) {
        int next_i = curr_i + move.first;
        int next_j = curr_j + move.second;
        exploreRoom(next_i, next_j, chart, chart_height, chart_width, vis);
    }
}

void solve(vector<vector<int>>& chart, int chart_height, int chart_width) {
    vector<vector<int>> vis(chart_height+1, vector<int>(chart_width+1, 0));

    int room_cnt = 0;
    for (int i = 0; i < chart_height; i++) {
        for (int j = 0; j < chart_width; j++) {
            if (chart[i][j] == 0 && vis[i][j] == 0) {
                room_cnt++;
                exploreRoom(i, j, chart, chart_height, chart_width, vis);
            }
        }
    }

    cout << room_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int chart_height, chart_width;
    cin >> chart_height >> chart_width;

    char ch;
    vector<vector<int>> chart(chart_height, vector<int>(chart_width, 0));
    for (int i = 0; i < chart_height; i++) {
        for (int j = 0; j < chart_width; j++) {
            cin >> ch;
            if (ch == '#') {
                chart[i][j] = 1;
            }
        }
    }

    solve(chart, chart_height, chart_width);
    
    return 0;
}