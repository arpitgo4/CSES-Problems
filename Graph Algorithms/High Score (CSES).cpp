// High Score (CSES)

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <bitset>

using namespace std;

// Time: O(VE + (V + E)) ~ O(VE)
// Space: O(V + E)

/**
 * 1. Bellman-ford will provide all the nodes involved in +ve cycles that are reachable 
 * from source (src_mask)
 * 2. DFS from destination vertex on transposed graph gives us the reachability vertex
 * set from destination (dest_mask)
 * 
 * If there is an intersection between src_mask & dest_mask, that means, destination vertex
 * is reachable from a +ve cycle that is also reachable from source. We can have infinitely
 * large score, hence, result is -1
 * Otherwise, traverse the shortest path tree from destination vertex to source vertex and
 * return the path weight (i.e. max score)
*/

using ll_t = long long;

const ll_t INF = LLONG_MAX;
const int MAX_ROOM_CNT = 2500;

class Tunnel {
public:
    int room_1_;
    int room_2_;
    ll_t score_;
    Tunnel(int room_1, int room_2, ll_t score) {
        room_1_ = room_1;
        room_2_ = room_2;
        score_ = score;
    }
};

void findSingleSourceShortestPath(
    int source,
    int room_cnt,
    vector<Tunnel>& tunnels,
    vector<ll_t>& dist
) {
    for (Tunnel& tunnel : tunnels) {
        tunnel.score_ = -tunnel.score_;
    }

    dist[source] = 0;
    for (int i = 0; i < room_cnt-1; i++) {
        for (auto& [ room_1, room_2, score ] : tunnels) {
            if (dist[room_1] != INF && dist[room_2] > dist[room_1] + score) {
                dist[room_2] = dist[room_1] + score;
            }
        }
    }
}

bool checkNegativeCycle(
    int room_cnt,
    vector<Tunnel>& tunnels,
    vector<ll_t>& dist,
    bitset<MAX_ROOM_CNT+1>& nodes_in_neg_cycle
) {
    bool any = false;
    for (auto& [ room_1, room_2, score ] : tunnels) {
        if (dist[room_1] != INF && dist[room_2] > dist[room_1] + score) {
            any = true;
            nodes_in_neg_cycle.set(room_2);
        }
    }

    return any;
}

void findReachableRooms(
    int curr_room,
    vector<vector<int>>& adj_list,
    bitset<MAX_ROOM_CNT+1>& nodes_reachable_from_dest
) {
    nodes_reachable_from_dest.set(curr_room);

    for (int next_room : adj_list[curr_room]) {
        if (!nodes_reachable_from_dest.test(next_room)) {
            findReachableRooms(
                next_room,
                adj_list,
                nodes_reachable_from_dest
            );
        }
    }
}

void solve(const int room_cnt, vector<Tunnel>& tunnels, int tunnel_cnt) {
    vector<ll_t> dist(room_cnt+1, INF);
    findSingleSourceShortestPath(
        1,
        room_cnt,
        tunnels,
        dist
    );

    bitset<MAX_ROOM_CNT+1> nodes_in_neg_cycle;
    bool neg_cyc_found = checkNegativeCycle(
        room_cnt,
        tunnels,
        dist,
        nodes_in_neg_cycle
    );

    if (!neg_cyc_found) {
        cout << (-dist[room_cnt]) << endl;
        return;
    }

    vector<vector<int>> adj_list(room_cnt+1, vector<int>());
    for (auto& [ room_1, room_2, _ ] : tunnels) {
        adj_list[room_2].push_back(room_1);
    }
    
    bitset<MAX_ROOM_CNT+1> nodes_reachable_from_dest;
    findReachableRooms(
        room_cnt,
        adj_list,
        nodes_reachable_from_dest
    );

    if ((nodes_in_neg_cycle & nodes_reachable_from_dest) == 0) {
        cout << (-dist[room_cnt]) << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int room_cnt, tunnel_cnt;
    cin >> room_cnt >> tunnel_cnt;

    vector<Tunnel> tunnels;
    int room_1, room_2;
    ll_t tunnel_score;
    for (int i = 0; i < tunnel_cnt; i++) {
        cin >> room_1 >> room_2 >> tunnel_score;
        tunnels.emplace_back(room_1, room_2, tunnel_score);
    }

    solve(room_cnt, tunnels, tunnel_cnt);

    return 0;
}