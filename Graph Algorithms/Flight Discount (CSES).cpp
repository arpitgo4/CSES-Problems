// Flight Discount (CSES)

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

vector<vector<pair<int,int>>> G;
vector<int> VIS;
vector<int> DIST;

void dijkstra(vector<vector<int>>& G, int source) {
    auto comp = [&](const pair<int,int>& p1, const pair<int,int>& p2) {
        return p1.first > p2.first;
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
    DIST[source] = 0;
    pq.push({ DIST[source], source });

    while (!pq.empty()) {

    }
}

void solve(int V, int E, vector<tuple<int,int,int>>& edges) {
    G.assign(V+1, vector<pair<int,int>>());
    VIS.assign(V+1, 0);
    DIST.assign(V+1, INT_MAX);

    for (tuple<int,int,int>& t : edges) {
        int u, v, w;
        tie(u,v,w) = t;
        G[u].push_back({ v, w });
    }

    dijkstra(G, 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<tuple<int,int,int>> edges(E);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(V, E, edges);

    return 0;
}