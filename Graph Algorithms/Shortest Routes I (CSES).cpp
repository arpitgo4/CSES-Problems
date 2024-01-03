// Shortest Routes I (CSES)

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;
using ll = long long;

// Time: O(V + ElogV)
// Space: O(V)

vector<ll> D;
vector<int> VIS;

void dijkstra(vector<vector<pair<int,ll>>>& G, int src) {
    auto comp = [&](const pair<ll,int>& P1, const pair<ll,int>& P2) {
        return P1.first > P2.first;
    };

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, decltype(comp)> pq(comp);
    D[src] = 0;
    pq.push({ D[src], src });

    while (!pq.empty()) {
        pair<ll,int> p = pq.top();
        pq.pop();

        int u = p.second;
        if (VIS[u] != 0)
            continue;
        VIS[u] = 1;

        for (pair<int,ll>& p : G[u]) {
            int v = p.first; ll w = p.second;
            if (D[v] > D[u] + w) {
                D[v] = D[u] + w;
                pq.push({ D[v], v });
            }
        }
    }
}

void solve(vector<vector<pair<int,ll>>>& G, int V, int E) {
    VIS.assign(V+1, 0);
    D.assign(V+1, LLONG_MAX);

    dijkstra(G, 1);

    int N = D.size();
    for (int i = 1; i < N; i++)
        cout << D[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    cin >> V >> E;

    vector<vector<pair<int,ll>>> G(V+1, vector<pair<int,ll>>());
    int u, v; ll w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        G[u].push_back({ v, w });
    }

    solve(G, V, E);

    return 0;
}