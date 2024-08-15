// Path Queries (CSES)
  
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Time: O()
// Space: O()

#define INF LLONG_MAX

typedef long long ll;
typedef pair<int,int> edge;

/**
 * Not so sure, because we have to take paths from root till required node
 * In this case, LCA is always the root node
 * 
 * Paths in a tree are required, LCA will be involved!
 * 
 * Do LCA pre-processing with Euler tours and Sparse table
*/

vector<vector<int>> T;
vector<ll> val;

void solve(vector<edge>& edges, int N) {
    T.assign(N+1, vector<int>());
    for (auto& [u, v] : edges) {
        T[u].push_back(v);
        T[v].push_back(u);
    }


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;

    val.assign(N, 0);
    for (int i = 0; i < N; i++)
        cin >> val[i];

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N);

    int type, u, x;
    for (int i = 0; i < Q; i++) {
        cin >> type >> u;
        if (type == 1) {
            cin >> x;
            // udpate value of node idx to x
        } else {
            // sum of nodes on path from root to node idx
        }
    }
    
    return 0;
}