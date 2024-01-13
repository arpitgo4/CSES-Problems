// Hamiltonian Flights (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
using ll = long long;

// Time: O(V^2 * 2^V)
// Space: O(V * 2^V)

const int MOD = 1e9 + 7;

vector<vector<int>> G, dp;
vector<int> VIS;

int dp_bitmask(int u, int mask, int V) {
    if (u == V)
        return mask == 0 ? 1 : 0;
    if (dp[u][mask] != -1)
        return dp[u][mask];

    int count = 0;
    for (int v = 1; v <= V; v++) {
        int idx = v-1;
        if ((mask & (1 << idx)) && G[u][v] != 0) {
            int u_count = dp_bitmask(v, mask ^ (1 << idx), V);
            count = (count + G[u][v] * 1ll * u_count) % MOD;
        }
    }

    return dp[u][mask] = count;
}

void reset_vis_status(int V) {
    VIS.clear();
    VIS.assign(V+1, 0);
}

int dfs(int idx, vector<int>& vertices, int end_vertex) {
    if (vertices[idx] == end_vertex)
        return 1;

    int u = vertices[idx];
    VIS[u] = 1;

    int count = 0;
    int v = vertices[idx+1];
    if (G[u][v] != 0 && VIS[v] == 0)             // only proceed if vertex is un-visited
        count = (count + dfs(idx+1, vertices, end_vertex)) % MOD;

    count = (count * G[u][v]) % MOD;

    VIS[u] = 2;
    return count;
}

// Time: O(V! * (V+E))
// Space: O(V+E)
int brute_solution(int V) {
    int count = 0;
    vector<int> vertices(V);
    for (int i = 1; i <= V; i++)
        vertices[i-1] = i;

    do {
        reset_vis_status(V);
        int hamiltonian_walks = dfs(0, vertices, V);
        count = (count + hamiltonian_walks) % MOD;
    } while (next_permutation(vertices.begin()+1, vertices.end()-1));

    return count;
}

void solve(int V, int E, vector<pair<int,int>>& edges) {
    G.assign(V+1, vector<int>(V+1, 0));
    VIS.assign(V+1, 0);
    dp.assign(V+1, vector<int>(1 << V, -1));
    for (pair<int,int>& e : edges) {
        int u = e.first, v = e.second;
        G[u][v]++;
    }
 
    // int count = brute_solution(V);

    int init_mask = (1 << V) - 1;               // 2^V-1 == (11111....V-times)
    init_mask ^= (1 << 0);           // remove vertex 1 from set, as we are already starting from it. Hence, not available in the set!
    int count = dp_bitmask(1, init_mask, V);

    cout << count;
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

    solve(V, E, edges);
    
    return 0;
}