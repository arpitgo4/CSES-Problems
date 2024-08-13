// Distinct Colors (CSES)
 
#include <iostream>
#include <vector>
#include <unordered_set>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N^2)

/**
 * Approaches,
 * 
 * 1. Can use Euler tour to linerize the tree. Subtrees will convert to subarrays
 * 2. Use DFS recursion and have a set of distinct colors for each subtree
 * 
 * Both above approaches, need efficient set merge technique.
 * Small to large merge heuristic is applicable.
 */

typedef pair<int,int> edge;
 
vector<vector<int>> T;
vector<unordered_set<int>> color_set;
vector<int> dp;

void dfs(int u, int p, vector<int>& color) {
    color_set[u].insert(color[u]);

    for (int v : T[u]) {
        if (v != p) {
            dfs(v, u, color);

            if (color_set[u].size() < color_set[v].size())
                swap(color_set[u], color_set[v]);

            for (int a : color_set[v])
                color_set[u].insert(a);
        }
    }

    dp[u] = color_set[u].size();
}

void solve(vector<edge>& edges, int N, vector<int>& color) {
    T.assign(N+1, vector<int>());
    color_set.assign(N+1, unordered_set<int>());
    dp.assign(N+1, -1);
    for (auto& [u, v] : edges) {
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, 1, color);

    for (int u = 1; u <= N; u++)
        cout << dp[u] << " ";
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<int> color(N+1);
    for (int i = 1; i <= N; i++)
        cin >> color[i];

    int u, v;
    vector<edge> edges(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> u >> v;
        edges[i] = { u, v };
    }

    solve(edges, N, color);
    
    return 0;
}