// Round Trip (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)

class Road {
public:
    int city_1_;
    int city_2_;
    Road(int city_1, int city_2) {
        city_1_ = city_1;
        city_2_ = city_2;
    }
};

void printRoundTrip(
    int start_city,
    int curr_city,
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
    for (int city : trip)
        cout << city << " ";
    cout << endl;
};

bool findRoundTrip(
    int curr_city,
    int curr_city_parent,
    vector<vector<int>>& adj_list,
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
            parent[next_city] = curr_city;
            trip_found = findRoundTrip(
                next_city,
                curr_city,
                adj_list,
                parent,
                vis
            );
        } else if (vis[next_city] != 0 && curr_city_parent != next_city) {
            trip_found = true;
            printRoundTrip(next_city, curr_city, parent);
        }
    }

    return trip_found;
}

void solve(int city_cnt, vector<Road>& roads, int road_cnt) {
    vector<vector<int>> adj_list(city_cnt+1, vector<int>());
    for (auto& [ city_1, city_2 ] : roads) {
        adj_list[city_1].push_back(city_2);
        adj_list[city_2].push_back(city_1);
    }

    vector<int> vis(city_cnt+1, 0);
    vector<int> parent(city_cnt+1, -1);

    bool trip_found = false;
    for (int i = 1; i <= city_cnt && !trip_found; i++) {
        if (vis[i] == 0) {
            trip_found = findRoundTrip(
                i,
                i,
                adj_list,
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
    
    int city_cnt, road_cnt;
    cin >> city_cnt >> road_cnt;

    int city_1, city_2;
    vector<Road> roads;
    for (int i = 0; i < road_cnt; i++) {
        cin >> city_1 >> city_2;
        roads.emplace_back(city_1, city_2);
    }

    solve(city_cnt, roads, road_cnt);
    
    return 0;
}