// Tree Distances II (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;

// Time: O(N)
// Space: O(N)

vector<vector<int>> T;
vector<int> DIST_ROOT, SIZE;
vector<int> DIST_SUM;

void print_vector(vector<int>& A) {
    int N = A.size();
    for (int i = 1; i < N; i++)
        cout << A[i] << " ";
    cout << endl;
}

int dfs(int u, int p, int level) {
    for (int v : T[u]) {
        if (v != p) {
            SIZE[u] += 1;
            DIST_SUM[u] += level;
            dfs(v, u, level+1);
        }
    }
}

void re_root(int u, int p) {
    if (DIST_SUM[u] == 0) {

    }

    for (int v : T[u]) {
        if (v != p)
            re_root(v, u);
    }
}
 
void solve(vector<pair<int,int>>& E, int V) {
    T.assign(V+1, vector<int>());
    DIST_ROOT.assign(V+1, 0);
    DIST_SUM.assign(V+1, 0);
    SIZE.assign(V+1, 1);

    for (pair<int,int>& e : E) {
        int u = e.first, v = e.second;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(1, -1, 0);
    print_vector(DIST_SUM);
    print_vector(SIZE);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V;
    cin >> V;

    vector<pair<int,int>> E(V-1);
    int u, v;
    for (int i = 0; i < V-1; i++) {
        cin >> u >> v;
        E[i] = { u, v };
    }

    solve(E, V);
    
    return 0;
}