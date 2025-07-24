// Flight Routes (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
 
using namespace std;
 
// Time: O(K * ElogE)
// Space: O(E)
 
using ll_t = long long;
using graph_edge_t = pair<ll_t,int>;
using graph_t = vector<vector<graph_edge_t>>;
using queue_state_t = pair<ll_t,int>;

const ll_t INF = LLONG_MAX;

class Flight {
public:
    int src_city_;
    int dest_city_;
    ll_t price_;
    Flight(int src_city, int dest_city, ll_t price) {
        src_city_ = src_city;
        dest_city_ = dest_city;
        price_ = price;
    }
};

void findShortestRoutePrices(
    int src_city,
    int dest_city,
    graph_t& adj_list,
    int city_cnt,
    int shortest_route_cnt,
    vector<ll_t>& shortest_prices
) {
    auto cmp = [&](auto& s1, auto& s2) {
        return s1.first > s2.first;
    };
    priority_queue<
        queue_state_t,
        vector<queue_state_t>,
        decltype(cmp)
    > city_queue(cmp);

    vector<ll_t> dist(city_cnt+1, INF);
    vector<int> city_relax_counter(city_cnt+1, 0);
    dist[src_city] = 0;
    city_relax_counter[src_city] = 0;
    city_queue.emplace(dist[src_city], src_city);

    while (!city_queue.empty()) {
        auto [ curr_dist, curr_city ] = city_queue.top();
        city_queue.pop();

        city_relax_counter[curr_city]++;
        if (city_relax_counter[curr_city] > shortest_route_cnt) {
            continue;
        }
        if (curr_city == dest_city) {
            shortest_prices.emplace_back(curr_dist);
        }
        
        for (auto& [ next_city, flight_price ] : adj_list[curr_city]) {
            if (dist[next_city] > dist[curr_city] + flight_price) {
                dist[next_city] = dist[curr_city] + flight_price;
                city_queue.emplace(dist[next_city], next_city);
            } else {
                ll_t next_city_price = curr_dist + flight_price;
                city_queue.emplace(next_city_price, next_city);
            }
        }
    }
}

void solve(
    int city_cnt,
    int shortest_route_cnt,
    vector<Flight>& flights,
    int flight_cnt
) {
    graph_t adj_list(city_cnt+1, vector<graph_edge_t>());
    for (auto& [ src_city, dest_city, price ] : flights) {
        adj_list[src_city].emplace_back(dest_city, price);
    }

    vector<ll_t> shortest_prices;
    findShortestRoutePrices(
        1,
        city_cnt,
        adj_list,
        city_cnt,
        shortest_route_cnt,
        shortest_prices
    );

    for (ll_t price : shortest_prices) {
        cout << price << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int city_cnt, flight_cnt, shortest_route_cnt;
    cin >> city_cnt >> flight_cnt >> shortest_route_cnt;

    int src_city, dest_city;
    ll_t price;
    vector<Flight> flights;
    for (int i = 0; i < flight_cnt; i++) {
        cin >> src_city >> dest_city >> price;
        flights.emplace_back(src_city, dest_city, price);
    }

    solve(city_cnt, shortest_route_cnt, flights, flight_cnt);
    
    return 0;
}