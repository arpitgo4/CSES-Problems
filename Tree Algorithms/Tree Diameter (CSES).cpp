// Tree Diameter (CSES)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time: O(N)
// Space: O(N)

typedef pair<int,int> edge;

vector<vector<int>> T;
vector<int> depth;

void dfs(int u, int p, int dep) {
    depth[u] = dep;
    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u, dep+1);
        }
    }
}

void solve(vector<edge>& edges, int N) {
    T.assign(N+1, vector<int>());
    for (edge& e : edges) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    depth.assign(N+1, 0);
    dfs(1, -1, 0);

    int max_dep = *max_element(depth.begin(), depth.end());
    int leaf = find(depth.begin(), depth.end(), max_dep) - depth.begin();

    depth.assign(N+1, 0);
    dfs(leaf, -1, 0);

    int diameter = *max_element(depth.begin(), depth.end());
    cout << diameter << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<edge> edges(N-1);
    int u, v;
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N);

    return 0;
}