// Labyrinth (CSES)
 
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;
 
// Time: O(N * M)
// Space: O(N * M)
 
using coord_t = pair<int,int>;
using move_t = tuple<int,int,char>;

vector<tuple<int,int,char>> moves {
    { -1, 0, 'U' },              // up
    { 1, 0, 'D' },               // down
    { 0, -1, 'L' },              // left
    { 0, 1, 'R' }                // right
};

void findShortestPath(
    coord_t& src,
    vector<vector<int>>& chart,
    int chart_height,
    int chart_width,
    coord_t& dest,
    vector<vector<int>>& vis,
    vector<vector<move_t>>& parent
) {

    queue<coord_t> coord_queue;
    coord_queue.push(src);
    auto& [ src_i, src_j ] = src;
    vis[src_i][src_j] = 1;
    
    while (!coord_queue.empty()) {
        auto [ curr_i, curr_j ] = coord_queue.front();
        coord_queue.pop();

        if (curr_i == dest.first && curr_j == dest.second) {
            return;
        }

        for (auto& [diff_i, diff_j, move_ch] : moves) {
            int next_i = curr_i + diff_i;
            int next_j = curr_j + diff_j;
            if (next_i >= 0 && 
                    next_i < chart_height && 
                    next_j >= 0 && 
                    next_j < chart_width && 
                    chart[next_i][next_j] == 0 &&
                    vis[next_i][next_j] == 0) {
                        coord_queue.push({ next_i, next_j });
                        parent[next_i][next_j] = { curr_i, curr_j, move_ch };
                        vis[next_i][next_j] = 1;
                    }
        }
    }
}

void solve(
    vector<vector<int>>& chart,
    int chart_height,
    int chart_width,
    coord_t& src,
    coord_t& dest
) {

    vector<vector<int>> vis(chart_height+1, vector<int>(chart_width+1, 0));
    vector<vector<move_t>> parent(chart_height+1, vector<move_t>(chart_width+1, {-1,-1,' '}));
    
    findShortestPath(
        src, 
        chart, 
        chart_height, 
        chart_width, 
        dest,
        vis,
        parent
    );

    auto [ dest_i, dest_j ] = dest;
    if (vis[dest_i][dest_j] == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<char> moves_taken;
        coord_t curr = dest;
        while (curr != src) {
            auto& [ curr_i, curr_j ] = curr;
            auto& [ par_i, par_j, move_ch ] = parent[curr_i][curr_j];
            moves_taken.push_back(move_ch);
            curr = { par_i, par_j };
        }

        cout << moves_taken.size() << endl;
        reverse(moves_taken.begin(), moves_taken.end());
        for (char move_ch : moves_taken) {
            cout << move_ch;
        }
        cout << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int chart_height, chart_width;
    cin >> chart_height >> chart_width;

    char ch;
    coord_t src, dest;
    vector<vector<int>> chart(chart_height, vector<int>(chart_width, 0));
    for (int i = 0; i < chart_height; i++) {
        for (int j = 0; j < chart_width; j++) {
            cin >> ch;
            if (ch == '#') {
                chart[i][j] = 1;    
            } else if (ch == 'A') {
                src = { i, j };
            } else if (ch == 'B') {
                dest = { i, j };
            }
        }
    }

    solve(chart, chart_height, chart_width, src, dest);
    
    return 0;
}