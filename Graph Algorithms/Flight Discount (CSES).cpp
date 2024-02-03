// Flight Discount (CSES)

#include <iostream>
#include <vector>
#include <climits>
#include <tuple>
#include <queue>

using namespace std;

typedef long long ll;
typedef tuple<ll,int,bool> state;
typedef pair<int,ll> edge;

// Time: O(V + 2ElogV)
// Space: O(V * 2) ~ O(V)

/**
 * We can solve this problem with simple recursion and speed it up with DP.
 * As problem, has an optimal substructure to it.
 * DP state: { vertex, coup_applied }
 * 
 * Dijkstra's algorithm is greedy algorithm. Greedy algorithm are also based on
 * problems having optimal substructure. We can extend Dijkstra's algorithm to solve
 * this problem by keeping the, 
 * state: { vertex_dist_from_source, vertex, coup_applied }
 * 
 * DP based approach is based on DFS traversal. And Dijkstra's is can be loosely said to 
 * be based on BFS traversal, only difference rather than having a vanilla queue, we 
 * are using a priority queue.
*/

vector<vector<pair<int,ll>>> G;
vector<vector<int>> dp;

void dijkstra(vector<vector<edge>>& G, int src, int dest) {
    auto comp = [&](state& s1, state& s2) {
        return get<0>(s1) > get<0>(s2);
    };
    priority_queue<state, vector<state>, decltype(comp)> pq(comp);        // min-heap

    ll min_price = LLONG_MAX;
    pq.push({ 0, src, false });

    while (!pq.empty()) {
        state p = pq.top();
        pq.pop();

        ll d; int u; bool coup_used;
        tie(d,u,coup_used) = p;

        // condition to avoid adding vertices again and again!
        // or, to avoid repeating same states over again!
        // problem state: (vertex, coup_used)
        if (dp[u][coup_used] == 1)
            continue;

        dp[u][coup_used] = 1;

        if (u == dest)
            min_price = min(min_price, d);
        
        // relax neighbouring vertices
        for (edge& e : G[u]) {
            int v = e.first; ll w = e.second;
            if (coup_used)
                pq.push({ d + w, v, true });
            else {
                pq.push({ d + (w/2), v, true });
                pq.push({ d + w, v, false });
            }
        }
    }

    cout << min_price;
}

void solve(int V, int E, vector<tuple<int,int,ll>>& edges) {
    G.assign(V+1, vector<pair<int,ll>>());
    dp.assign(V+1, vector<int>(2, -1));

    for (tuple<int,int,ll>& t : edges) {
        int u, v; ll w;
        tie(u,v,w) = t;
        G[u].push_back({ v, w });
    }

    dijkstra(G, 1, V);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<tuple<int,int,ll>> edges(E);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(V, E, edges);

    return 0;
}