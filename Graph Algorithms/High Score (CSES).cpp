// High Score (CSES)

#include <iostream>
#include <vector>

using namespace std;

void solve(vector<tuple<int,int,int>>& edges, int E, int V) {
    
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

    solve(edges, E, V);

    return 0;
}