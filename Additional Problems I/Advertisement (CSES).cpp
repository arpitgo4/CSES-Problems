// Advertisement (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
/**
 * Using Monotonic stack for 
 * previous and next smaller/greater
 * values.
 * 
 * For a ith fence,
 * 1. We need left smaller board
 * 2. We need right smaller board
 * 
 * All boards between above two boards,
 * will give the max possible width of
 * advertisement and board[i] will the 
 * height.
 * 
 * Max of all possible areas for each fence,
 * will be the result.
 */

using ll_t = long long;

void solve(
    vector<int>& board_heights,
    int fence_wid
) {
    stack<pair<int,int>> prev_shorter;                          // monotonically increasing stack
    vector<int> prev_shorter_idx(fence_wid, 0);
    for (int i = 0; i < fence_wid; i++) {
        int curr_height = board_heights[i];
        while (!prev_shorter.empty() && 
                prev_shorter.top().first >= curr_height) {
            prev_shorter.pop();
        }

        if (!prev_shorter.empty()) {
            prev_shorter_idx[i] = prev_shorter.top().second+1;
        }

        prev_shorter.emplace(curr_height, i);
    }

    stack<pair<int,int>> next_shorter;                          // monotonically increasing stack
    vector<int> next_shorter_idx(fence_wid, fence_wid-1);
    for (int i = fence_wid-1; i >= 0; i--) {
        int curr_height = board_heights[i];
        while (!next_shorter.empty() && 
                next_shorter.top().first >= curr_height) {
            next_shorter.pop();
        }

        if (!next_shorter.empty()) {
            next_shorter_idx[i] = next_shorter.top().second-1;
        }
        
        next_shorter.emplace(curr_height, i);
    }

    ll_t max_area = 0;
    for (int i = 0; i < fence_wid; i++) {
        int prev_board_idx = prev_shorter_idx[i];
        int next_board_idx = next_shorter_idx[i];
        int adver_wid = next_board_idx - prev_board_idx + 1;
        max_area = max<ll_t>(max_area, adver_wid * 1ll * board_heights[i]);
    }

    cout << max_area << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int fence_wid;
    cin >> fence_wid;

    vector<int> board_heights(fence_wid);
    for (int i = 0; i < fence_wid; i++) {
        cin >> board_heights[i];
    }

    solve(board_heights, fence_wid);
    
    return 0;
}