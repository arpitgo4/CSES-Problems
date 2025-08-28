// Tree Diameter (CSES)
 
#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
using tree_t = vector<vector<int>>;

class Edge {
public:
    int node_1_;
    int node_2_;
    Edge(int node_1, int node_2) {
        node_1_ = node_1;
        node_2_ = node_2;
    }
};

int findFarthestNode(
    int root_node,
    tree_t& tree,
    int node_cnt,
    vector<int>& dist
) {
    vector<int> parent(node_cnt+1, 0);
    iota(parent.begin(), parent.end(), 0);

    queue<int> node_queue;
    node_queue.emplace(root_node);

    while (!node_queue.empty()) {
        int curr_node = node_queue.front();
        node_queue.pop();

        for (int next_node : tree[curr_node]) {
            if (next_node != parent[curr_node]) {
                parent[next_node] = curr_node;
                dist[next_node] = dist[curr_node] + 1;
                node_queue.emplace(next_node);
            }
        }
    }

    int farthest_node = -1;
    int farthest_node_dist = 0;
    for (int i = 1; i <= node_cnt; i++) {
        if (dist[i] > farthest_node_dist) {
            farthest_node_dist = dist[i];
            farthest_node = i;
        }
    }

    return farthest_node;
}

void solve(
    int node_cnt,
    vector<Edge>& edges
) {
    tree_t tree(node_cnt+1, vector<int>());
    for (auto& [ node_1, node_2 ] : edges) {
        tree[node_1].push_back(node_2);
        tree[node_2].push_back(node_1);
    }

    vector<int> dist(node_cnt+1, 0);
    int farthest_node_from_root = findFarthestNode(
        1,
        tree,
        node_cnt,
        dist
    );

    dist.assign(node_cnt+1, 0);
    int farthest_node = findFarthestNode(
        farthest_node_from_root,
        tree,
        node_cnt,
        dist
    );

    int diameter = dist[farthest_node];
    cout << diameter << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int node_cnt;
    cin >> node_cnt;

    int node_1, node_2;
    vector<Edge> edges;
    for (int i = 0; i < node_cnt-1; i++) {
        cin >> node_1 >> node_2;
        edges.emplace_back(node_1, node_2);
    }

    solve(node_cnt, edges);
    
    return 0;
}