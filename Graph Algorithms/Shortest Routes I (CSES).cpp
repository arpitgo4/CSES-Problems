// Shortest Routes I (CSES)
 
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
 
using namespace std;
 
// Time: O(ElogV)
// Space: O(V)
 
using ll_t = long long;
using graph_t = vector<vector<pair<int,ll_t>>>;
using queue_state_t = pair<ll_t,int>;

const ll_t INF = LLONG_MAX;

class Flight {
public:
    int src_;
    int dest_;
    ll_t duration_;

    Flight(int src, int dest, ll_t duration) {
        src_ = src;
        dest_ = dest;
        duration_ = duration;
    }
};


void findShortestPathFromSource(
    int source,
    graph_t& adj_list,
    int city_cnt,
    vector<ll_t>& dist
) {
    vector<int> vis(city_cnt+1, 0);

    auto cmp = [&](auto& s1, auto& s2) {
        return s1.first > s2.first;
    };
    priority_queue<queue_state_t, vector<queue_state_t>, decltype(cmp)> city_queue(cmp);
    
    dist[source] = 0;
    city_queue.push({ dist[source], source });
    vis[source] = 1;

    while (!city_queue.empty()) {
        auto [ _, curr_city ] = city_queue.top();
        city_queue.pop();

        if (vis[curr_city] == 2)
            continue;

        for (auto& [ next_city, duration ] : adj_list[curr_city]) {
            if (dist[next_city] > dist[curr_city] + duration) {
                dist[next_city] = dist[curr_city] + duration;
                city_queue.push({ dist[next_city], next_city });
                vis[next_city] = 1;
            }
        }

        vis[curr_city] = 2;
    }
};

void solve(int city_cnt, vector<Flight>& flights, int flight_cnt) {
    graph_t adj_list(city_cnt+1, vector<pair<int,ll_t>>());
    for (Flight& flight : flights) {
        adj_list[flight.src_]
            .push_back({ flight.dest_, flight.duration_ });
    }

    vector<ll_t> dist(city_cnt+1, INF);
    findShortestPathFromSource(1, adj_list, city_cnt, dist);

    for (int i = 1; i <= city_cnt; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int city_cnt, flight_cnt;
    cin >> city_cnt >> flight_cnt;

    int src, dest;
    ll_t duration;
    vector<Flight> flights;
    for (int i = 0; i < flight_cnt; i++) {
        cin >> src >> dest >> duration;
        flights.emplace_back(src, dest, duration);
    }

    solve(city_cnt, flights, flight_cnt);
    
    return 0;
}