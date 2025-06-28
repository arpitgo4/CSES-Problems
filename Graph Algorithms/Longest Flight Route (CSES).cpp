// Longest Flight Route (CSES)
 
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
using graph_t = vector<vector<int>>;

const int NEG_INF = INT_MIN;

class Flight {
public:
    int src_;
    int dest_;
    Flight(int src, int dest) {
        src_ = src;
        dest_ = dest;
    }
};

int findLongestPathInDAG(
    int curr_city,
    graph_t& adj_list,
    int dest_city,
    vector<int>& dp,
    vector<int>& next
) {

    if (curr_city == dest_city)
        return dp[dest_city] = 0;
    if (dp[curr_city] != -1)
        return dp[curr_city];

    // return -INF, when dest city is not reachable from
    // a certain path in DAG
    int max_route_len = NEG_INF;
    for (int next_city : adj_list[curr_city]) {
        int route_len = 1 + findLongestPathInDAG(
            next_city,
            adj_list,
            dest_city,
            dp,
            next
        );

        if (route_len > max_route_len) {
            max_route_len = route_len;
            next[curr_city] = next_city;
        }
    }

    return dp[curr_city] = max_route_len;
}

void solve(int city_cnt, vector<Flight>& flights, int flight_cnt) {
    graph_t adj_list(city_cnt+1, vector<int>());
    for (Flight& flight : flights) {
        adj_list[flight.src_].push_back(flight.dest_);
    }

    int start_city_idx = 1;
    int dest_city_idx = city_cnt;

    vector<int> dp(city_cnt+1, -1);
    vector<int> next(city_cnt+1, 0);
    iota(next.begin(), next.end(), 0);
    findLongestPathInDAG(
        start_city_idx,
        adj_list,
        dest_city_idx,
        dp,
        next
    );
    
    if (dp[dest_city_idx] == -1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    int curr_city = start_city_idx;
    vector<int> route;
    while (curr_city != dest_city_idx) {
        route.push_back(curr_city);
        curr_city = next[curr_city];
    }
    route.push_back(dest_city_idx);

    cout << route.size() << endl;
    for (int city : route) {
        cout << city << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int city_cnt, flight_cnt;
    cin >> city_cnt >> flight_cnt;

    int from_city, to_city;
    vector<Flight> flights;
    for (int i = 0; i < flight_cnt; i++) {
        cin >> from_city >> to_city;
        flights.emplace_back(from_city, to_city);
    }

    solve(city_cnt, flights, flight_cnt);
    
    return 0;
}