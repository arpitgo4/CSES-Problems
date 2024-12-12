// Shortest Routes I (CSES)

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <tuple>

using namespace std;

// Time: O(V + ElogV)
// Space: O(V)

#define INF LLONG_MAX

typedef long long ll;
typedef tuple<int,int,ll> edge;
typedef pair<int,ll> g_edge;
typedef pair<ll,int> state;

vector<vector<g_edge>> G;

vector<int> vis;
vector<ll> D;

void dijkstra(int src) {
    auto cmp = [&](const state& s1, const state& s2) {
        return s1.first > s2.first;
    };
    priority_queue<state, vector<state>, decltype(cmp)> pq(cmp);            // default pq is max_heap, but with cmp it is min_heap

    D[src] = 0;
    pq.push({ D[src], src });

    while (!pq.empty()) {
        auto [ _, u ] = pq.top();
        pq.pop();

        if (vis[u] == 1)
            continue;
        vis[u] = 1;

        for (g_edge& e : G[u]) {
            auto& [ v, w ] = e;
            if (D[v] > D[u] + w) {
                D[v] = D[u] + w;
                pq.push({ D[v], v });
            }
        }
    }
}

void solve(vector<edge>& edges, int E, int V) {
    G.assign(V+1, vector<g_edge>());
    vis.assign(V+1, 0);
    D.assign(V+1, INF);

    int u, v; ll w;
    for (edge& e : edges) {
        tie(u, v, w) = e;
        G[u].push_back({ v, w });
    }

    dijkstra(1);

    for (int u = 1; u <= V; u++)
        cout << D[u] << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    int u, v; ll w;
    vector<edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(edges, E, V);

    return 0;
}