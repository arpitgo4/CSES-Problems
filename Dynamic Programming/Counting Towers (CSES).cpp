// Counting Towers (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(H^2)
// Space: O(H*2) ~ O(H)

const int MOD = 1e9 + 7;
const int MAX_H = 1e6 + 1;
const int MAX_W = 2 + 1;
vector<vector<int>> cache(MAX_H, vector<int>(MAX_W, -1));

int dfs(int H, int W) {
    if (H == 0)
        return 1;
    if (cache[H][W] != -1)
        return cache[H][W];
    if (W == 1) {
        int count = 0;
        for (int h = 1; h <= H; h++)
            count = (count + dfs(H-h, 1)) % MOD;
        return count;
    }

    int count = 0;
    for (int h = 1; h <= H; h++) {
        int a = dfs(H-h, 2);
        int b = dfs(h, 1);          // NOTE: what about the second spot, dfs(h, 1)
        count = (count + ((a + b) % MOD) % MOD);
    }

    return cache[H][W] = count;
}

void solve(int H) {
    int count = dfs(H, 2);

    cout << count << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    int H;
    while (T--) {
        cin >> H;
        solve(H);
    }

    return 0;
}