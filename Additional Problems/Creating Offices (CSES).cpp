// Creating Offices (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
#define edge pair<int,int>

vector<vector<int>> T;

void solve(int N, int D, vector<edge>& edges) {
    T.assign(N+1, vector<int>());
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, D;
    cin >> N >> D;

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(N, D, edges);
    
    return 0;
}