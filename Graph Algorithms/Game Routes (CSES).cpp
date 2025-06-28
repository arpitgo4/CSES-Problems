// Game Routes (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)

using ll_t = long long;
using graph_t = vector<vector<int>>;

const ll_t MOD = 1e9 + 7;

class Teleporter {
public:
    int src_;
    int dest_;
    Teleporter(int src, int dest) {
        src_ = src;
        dest_ = dest;
    }
};

ll_t countWaysToReachDestination(
    int curr_level,
    int dest_level,
    graph_t& adj_list,
    vector<ll_t>& dp
) {
    if (curr_level == dest_level)
        return 1;
    if (dp[curr_level] != -1)
        return dp[curr_level];

    ll_t ways_cnt = 0;
    for (int next_level : adj_list[curr_level]) {
        ll_t curr_cnt = countWaysToReachDestination(
            next_level,
            dest_level,
            adj_list,
            dp
        );

        ways_cnt = (ways_cnt + curr_cnt) % MOD;
    }

    return dp[curr_level] = ways_cnt;
}

void solve(
    int level_cnt,
    vector<Teleporter>& teleporters,
    int teleporter_cnt
) {
    
    graph_t adj_list(level_cnt+1, vector<int>());
    for (Teleporter& teleporter : teleporters) {
        adj_list[teleporter.src_].push_back(teleporter.dest_);
    }

    vector<ll_t> dp(level_cnt+1, -1);
    ll_t ways_cnt = countWaysToReachDestination(
        1,
        level_cnt,
        adj_list,
        dp
    );

    cout << ways_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int level_cnt, teleporter_cnt;
    cin >> level_cnt >> teleporter_cnt;

    int from_level, to_level;
    vector<Teleporter> teleporters;
    for (int i = 0; i < teleporter_cnt; i++) {
        cin >> from_level >> to_level;
        teleporters.emplace_back(from_level, to_level);
    }

    solve(level_cnt, teleporters, teleporter_cnt);
    
    return 0;
}