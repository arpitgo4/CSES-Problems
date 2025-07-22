// Flight Routes Check (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)

using graph_t = vector<vector<int>>;

class Flight {
public:
    int src_city_;
    int dest_city_;
    Flight(int src_city, int dest_city) {
        src_city_ = src_city;
        dest_city_ = dest_city;
    }
};

void findStronglyConnectedComponents(
    int curr_city,
    graph_t& adj_list,
    int& curr_time,
    vector<int>& vis,
    stack<int>& city_stack,
    vector<bool>& on_city_stack,
    vector<int>& start_time,
    vector<int>& low_link,
    vector<vector<int>>& scc_list
) {
    vis[curr_city] = 1;
    start_time[curr_city] = curr_time++;
    low_link[curr_city] = start_time[curr_city];
    city_stack.push(curr_city);
    on_city_stack[curr_city] = true;

    for (int next_city : adj_list[curr_city]) {
        if (vis[next_city] == 0) {
            findStronglyConnectedComponents(
                next_city,
                adj_list,
                curr_time,
                vis,
                city_stack,
                on_city_stack,
                start_time,
                low_link,
                scc_list
            );
            low_link[curr_city] = min(
                low_link[curr_city], 
                low_link[next_city]
            );
        } else if (on_city_stack[next_city]) {
            low_link[curr_city] = min(
                low_link[curr_city],
                start_time[next_city]
            );
        }
    }

    if (low_link[curr_city] == start_time[curr_city]) {
        int city_on_stack;
        scc_list.emplace_back();
        vector<int>& scc = scc_list.back();
        do {
            city_on_stack = city_stack.top();
            city_stack.pop();
            on_city_stack[city_on_stack] = false;
            scc.push_back(city_on_stack);
        } while (city_on_stack != curr_city);
    }
}
 
void solve(
    int city_cnt,
    vector<Flight>& flights,
    int flight_cnt
) {
    graph_t adj_list(city_cnt+1, vector<int>());
    for (auto& [ src_city, dest_city ] : flights) {
        adj_list[src_city].push_back(dest_city);
    }

    int time = 0;
    vector<int> vis(city_cnt+1, 0);
    stack<int> city_stack;
    vector<bool> on_city_stack(city_cnt+1, false);
    vector<int> start_time(city_cnt+1, -1);
    vector<int> low_link(city_cnt+1, -1);
    vector<vector<int>> scc_list;

    for (int curr_city = 1; curr_city <= city_cnt; curr_city++) {
        if (vis[curr_city] == 0) {
            findStronglyConnectedComponents(
                curr_city,
                adj_list,
                time,
                vis,
                city_stack,
                on_city_stack,
                start_time,
                low_link,
                scc_list
            );    
        }
    }

    if (scc_list.size() == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
        vector<int>& scc_1 = scc_list[0];
        vector<int>& scc_2 = scc_list[1];
        cout << scc_1.front() << " " << scc_2.front() << endl;
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int city_cnt, flight_cnt;
    cin >> city_cnt >> flight_cnt;

    int src_city, dest_city;
    vector<Flight> flights;
    for (int i = 0; i < flight_cnt; i++) {
        cin >> src_city >> dest_city;
        flights.emplace_back(src_city, dest_city);
    }

    solve(city_cnt, flights, flight_cnt);
    
    return 0;
}