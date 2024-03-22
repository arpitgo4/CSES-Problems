// Tree Matching (CSES)
 
#include <iostream>
#include <vector>
#include <bitset>
 
using namespace std;
 
/**
 * Maximum Cardinality Matching in Tree (MCMT)
 * 
 * Approach is to start picking edges from leaf nodes. As soon as the leaf edge is picked
 * adjacent edges are not eligible for matching and newer edges can be treated as leaf edges
*/

// Time: O(N)
// Space: O(N)

typedef pair<int,int> edge;
 
const int MAX_N = 2e5;

vector<vector<int>> T;
bitset<MAX_N+1> mask;

void dfs(int u, int p) {
    for (int v : T[u]) {
        if (v != p)
            dfs(v, u);
    }

    if (!mask.test(u) && p != -1 && !mask.test(p))
        mask.set(u).set(p);
}

void solve(vector<edge>& edges, int N) {
    T.assign(N+1, vector<int>());
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, -1);
    cout << (mask.count()/2) << endl;
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