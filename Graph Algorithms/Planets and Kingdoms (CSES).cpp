// Planets and Kingdoms (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#include <unordered_map>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
using graph_t = vector<vector<int>>;

class Teleporter {
public:
    int src_planet_;
    int dest_planet_;
    Teleporter(int src_planet, int dest_planet) {
        src_planet_ = src_planet;
        dest_planet_ = dest_planet;
    }
};

void findStronglyConnectedComponents(
    int curr_planet,
    graph_t& adj_list,
    int& time,
    stack<int>& planet_stack,
    vector<bool>& on_planet_stack,
    vector<int>& parent,
    vector<int>& low_link,
    vector<int>& start_time,
    vector<int>& vis
) {

    vis[curr_planet] = 1;
    start_time[curr_planet] = time++;
    low_link[curr_planet] = start_time[curr_planet];
    planet_stack.push(curr_planet);
    on_planet_stack[curr_planet] = true;

    for (int next_planet : adj_list[curr_planet]) {
        if (vis[next_planet] == 0) {
            findStronglyConnectedComponents(
                next_planet,
                adj_list,
                time,
                planet_stack,
                on_planet_stack,
                parent,
                low_link,
                start_time,
                vis
            );

            low_link[curr_planet] = min(
                low_link[curr_planet],
                low_link[next_planet]
            );
        } else if (on_planet_stack[next_planet]) {
            low_link[curr_planet] = min(
                low_link[curr_planet],
                start_time[next_planet]
            );
        }
    }
    
    if (low_link[curr_planet] == start_time[curr_planet]) {
        int planet_on_stack;
        do {
            planet_on_stack = planet_stack.top();
            planet_stack.pop();
            on_planet_stack[planet_on_stack] = false;
            parent[planet_on_stack] = curr_planet;
        } while (planet_on_stack != curr_planet);
    }
}

void solve(
    int planet_cnt,
    vector<Teleporter>& teleporters,
    int teleporter_cnt
) {
    graph_t adj_list(planet_cnt+1, vector<int>());
    for (auto& [ src_planet, dest_planet ] : teleporters) {
        adj_list[src_planet].push_back(dest_planet);
    }

    int time = 0;
    vector<int> vis(planet_cnt+1, 0);
    vector<int> low_link(planet_cnt+1, -1);
    vector<int> start_time(planet_cnt+1, 0);
    vector<int> parent(planet_cnt+1, -1);
    vector<bool> on_planet_stack(planet_cnt+1, false);
    stack<int> planet_stack;
    iota(parent.begin(), parent.end(), 0);

    for (int curr_planet = 1; 
        curr_planet <= planet_cnt; 
        curr_planet++) {
            if (vis[curr_planet] == 0) {
                findStronglyConnectedComponents(
                    curr_planet,
                    adj_list,
                    time,
                    planet_stack,
                    on_planet_stack,
                    parent,
                    low_link,
                    start_time,
                    vis
                );
            }
    }

    int label_counter = 0;
    unordered_map<int,int> parent_label_mapping;
    for (int curr_planet = 1; 
        curr_planet <= planet_cnt; 
        curr_planet++) {

        int parent_planet = parent[curr_planet];
        if (parent_label_mapping.find(parent_planet) == 
                parent_label_mapping.end()) {

            parent_label_mapping[parent_planet] = ++label_counter;
        }
    }

    cout << parent_label_mapping.size() << endl;
    for (int curr_planet = 1; 
        curr_planet <= planet_cnt; 
        curr_planet++) {

        int parent_planet = parent[curr_planet];
        cout << parent_label_mapping[parent_planet] << " ";    
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int planet_cnt, teleporter_cnt;
    cin >> planet_cnt >> teleporter_cnt;

    int src_planet, dest_planet;
    vector<Teleporter> teleporters;
    for (int i = 0; i < teleporter_cnt; i++) {
        cin >> src_planet >> dest_planet;
        teleporters.emplace_back(
            src_planet,
            dest_planet
        );
    }

    solve(planet_cnt, teleporters, teleporter_cnt);
    
    return 0;
}