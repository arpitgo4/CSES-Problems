// Round Trip II (CSES)
 
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
class Flight {
public:
    int start_city_;
    int dest_city_;
    Flight(int start_city, int dest_city) {
        start_city_ = start_city;
        dest_city_ = dest_city;
    }
};

void printRoundTrip(
    int curr_city,
    int start_city,
    vector<int>& parent
) {
    vector<int> trip{ start_city };
    int __curr_city = curr_city;
    do {
        trip.push_back(__curr_city);
        __curr_city = parent[__curr_city];
    } while (__curr_city != start_city);
    trip.push_back(start_city);

    reverse(trip.begin(), trip.end());

    cout << trip.size() << endl;
    for (int city : trip) {
        cout << city << " ";
    }
    cout << endl;
}

bool findRoundTrip(
    int curr_city,
    vector<vector<int>>& adj_list,
    vector<int>& depth,
    vector<int>& parent,
    vector<int>& vis
) {
    vis[curr_city] = 1;

    bool trip_found = false;
    for (int next_city : adj_list[curr_city]) {
        if (trip_found) {
            break;
        }

        if (vis[next_city] == 0) {
            depth[next_city] = depth[curr_city] + 1;
            parent[next_city] = curr_city;
            trip_found = findRoundTrip(
                next_city,
                adj_list,
                depth,
                parent,
                vis
            );
        } else if (vis[next_city] == 1) {
            int city_cnt_in_cycle = depth[curr_city] - depth[next_city] + 1;
            if (city_cnt_in_cycle >= 2) {
                trip_found = true;
                printRoundTrip(curr_city, next_city, parent);
            }
        }
    }

    vis[curr_city] = 2;

    return trip_found;
}

void solve(
    int city_cnt,
    vector<Flight>& flights,
    int flight_cnt
) {
    vector<vector<int>> adj_list(city_cnt+1, vector<int>());
    for (auto& [ start_city, dest_city ] : flights) {
        adj_list[start_city].push_back(dest_city);
    }

    vector<int> vis(city_cnt+1, 0);
    vector<int> depth(city_cnt+1, -1);
    vector<int> parent(city_cnt+1, -1);
    iota(parent.begin(), parent.end(), 0);

    bool trip_found = false;
    for (int i = 1; i <= city_cnt && !trip_found; i++) {
        if (vis[i] == 0) {
            depth[i] = 0;
            trip_found = findRoundTrip(
                i,
                adj_list,
                depth,
                parent,
                vis
            );
        }
    }
    
    if (!trip_found) {
        cout << "IMPOSSIBLE" << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int city_cnt, flight_cnt;
    cin >> city_cnt >> flight_cnt;

    int start_city, dest_city;
    vector<Flight> flights;
    for (int i = 0; i < flight_cnt; i++) {
        cin >> start_city >> dest_city;
        flights.emplace_back(start_city, dest_city);
    }

    solve(city_cnt, flights, flight_cnt);
    
    return 0;
}