// Flight Routes (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <tuple>
 
using namespace std;
using ll = long long;

// Time: O(V + KElogV) ~ O(KElogV)
// Space: O(V)

vector<vector<pair<int,ll>>> G;
vector<int> counter;

void dijkstra(int src, int K, int dest) {
    auto comp = [&](auto& p1, auto& p2) {
        return p1.first > p2.first;
    };
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, decltype(comp)> pq(comp);  // min-heap

    pq.push({ 0, src });

    while (!pq.empty() && counter[dest] < K) {
        auto p = pq.top();
        pq.pop();

        int u = p.second;
        ll d = p.first;

        counter[u]++;
        if (u == dest)
            cout << d << " ";

        if (counter[u] <= K) {
            for (auto& e : G[u]) {
                int v = e.first; ll w = e.second;
                pq.push({ d+w, v });
            }
        }
    }
}

void solve(int V, int E, int K, vector<tuple<int,int,int>>& edges) {
    G.assign(V+1, vector<pair<int,ll>>());
    counter.assign(V+1, 0);

    for (tuple<int,int,int>& t : edges) {
        int u, v; ll w;
        tie(u,v,w) = t;
        G[u].push_back({ v, w });
    }

    dijkstra(1, K, V);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E, K;
    cin >> V >> E >> K;

    vector<tuple<int,int,int>> edges(E);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }

    solve(V, E, K, edges);   
    
    return 0;
}