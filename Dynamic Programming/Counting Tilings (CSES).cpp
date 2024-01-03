// Counting Tilings (CSES)

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
vector<vector<int>> cache;

int dfs(int N, int M) {
    
}

void solve(int N, int M) {
    cache.assign(N, vector<int>(M, -1));
    int count = dfs(0, 0);

    cout << count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    solve(N, M);


    return 0;
}