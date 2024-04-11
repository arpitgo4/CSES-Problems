// Finding a Centroid (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
typedef pair<int,int> edge;

vector<vector<int>> T;
vector<int> sz;

int find_centroid(int u, int p, int N) {
    for (int v : T[u]) {
        if (v != p && sz[v] > N/2)
            return find_centroid(v, u, N);
    }

    return u;
}

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

void solve(vector<edge>& edges, int N) {
    T.assign(N+1, vector<int>());
    sz.assign(N+1, 0);
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, -1);

    int centroid = find_centroid(1, -1, N);
    cout << centroid << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N);
    
    return 0;
}