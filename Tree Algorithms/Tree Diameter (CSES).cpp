// Tree Diameter (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N)
// Space: O(N)

typedef pair<int,int> edge;

vector<vector<int>> T;

int diameter = 0;

int dfs(int u, int p) {
    int max_1 = 0, max_2 = 0;
    for (int v : T[u]) {
        if (v != p) {
            int dist = 1 + dfs(v, u);
            if (dist > max_1) {
                max_2 = max_1;
                max_1 = dist;
            } else if (dist > max_2)
                max_2 = dist;
        }
    }

    diameter = max({ diameter, max_1, max_1 + max_2 });

    return max_1;
}

void solve(vector<edge>& E, int V) {
    T.assign(V+1, vector<int>());
    for (edge& p : E) {
        int u = p.first, v = p.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, -1);

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