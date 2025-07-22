// Cycle Finding (CSES)
 
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
 
using namespace std;
 
// Time: O(VE)
// Space: O(V + E)
 
using ll_t = long long;

class Edge {
public:
    int node_1_;
    int node_2_;
    ll_t weight_;
    Edge(int node_1, int node_2, ll_t weight) {
        node_1_ = node_1;
        node_2_ = node_2;
        weight_ = weight;
    }
};

bool checkNegativeCycle(
    int node_cnt,
    vector<Edge>& edges,
    vector<ll_t>& dist,
    vector<bool>& node_in_neg_cycle,
    vector<int>& parent
) {
    for (int i = 0; i < node_cnt-1; i++) {
        for (auto& [ node_1, node_2, weight ] : edges) {
            if (dist[node_2] > dist[node_1] + weight) {
                dist[node_2] = dist[node_1] + weight;
                parent[node_2] = node_1;
            }
        }
    }

    bool neg_cycle_found = false;
    for (auto& [ node_1, node_2, weight ] : edges) {
        if (dist[node_2] > dist[node_1] + weight) {
            neg_cycle_found = true;
            dist[node_2] = dist[node_1] + weight;
            parent[node_2] = node_1;
            node_in_neg_cycle[node_2] = true;
        }
    }

    return neg_cycle_found;
}

void solve(int node_cnt, vector<Edge>& edges, int edge_cnt) {
    vector<ll_t> dist(node_cnt+1, 0);
    vector<int> parent(node_cnt+1, -1);
    iota(parent.begin(), parent.end(), 0);
    vector<bool> node_in_neg_cycle(node_cnt+1, false);

    bool negativeCycleFound = checkNegativeCycle(
        node_cnt,
        edges,
        dist,
        node_in_neg_cycle,
        parent
    );

    if (!negativeCycleFound) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    int curr_node = 0;
    for (int i = 1; i <= node_cnt; i++) {
        if (node_in_neg_cycle[i]) {
            curr_node = i;
            break;
        }
    }

    // with this loop, we can be sure that
    // we will enter the cycle
    for (int i = 0; i < node_cnt-1; i++) {
        curr_node = parent[curr_node];
    }

    vector<int> cycle;
    int cycle_start_node = curr_node;
    do {
        cycle.push_back(curr_node);
        curr_node = parent[curr_node];
    } while(curr_node != cycle_start_node);
    cycle.push_back(cycle_start_node);

    reverse(cycle.begin(), cycle.end());
    for (int node : cycle) {
        cout << node << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int node_cnt, edge_cnt;
    cin >> node_cnt >> edge_cnt;

    int node_1, node_2;
    ll_t weight;
    vector<Edge> edges;
    for (int i = 0; i < edge_cnt; i++) {
        cin >> node_1 >> node_2 >> weight;
        edges.emplace_back(node_1, node_2, weight);
    }

    solve(node_cnt, edges, edge_cnt);
    
    return 0;
}