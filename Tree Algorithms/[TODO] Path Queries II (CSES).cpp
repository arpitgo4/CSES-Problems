// Path Queries II (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
 
// Time: O()
// Space: O()
 
#define INF LLONG_MAX

typedef pair<int,int> edge;
 
vector<vector<int>> T;

void solve(vector<edge>& edges, int N) {
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
    
    int N, Q;
    cin >> N >> Q;

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N);

    int type, s, x, a, b;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> s >> x;

        } else {
            cin >> a >> b;

        }
    }
    
    return 0;
}