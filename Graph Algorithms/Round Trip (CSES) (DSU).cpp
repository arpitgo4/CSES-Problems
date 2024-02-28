// Round Trip (CSES) (DSU)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
vector<vector<int>> G;
 
void solve(vector<pair<int,int>>& edges, int V, int E) {
    G.assign(V+1, vector<int>());
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V, E;
    cin >> V >> E;

    int u, v;
    vector<pair<int,int>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        edges[i] = { u, v };    
    }

    solve(edges, V, E);   
    
    return 0;
}