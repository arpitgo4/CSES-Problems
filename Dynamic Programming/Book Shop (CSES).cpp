// Book Shop (CSES)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Time: O(N * MAX_PRICE)
// Space: O(N * MAX_PRICE)

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void solve_iteratively(vector<int>& prices, vector<int>& pages, int N, int max_price) {
    vector<vector<int>> dp(N, vector<int>(max_price+1, 0));

    for (int curr_max_price = 0; curr_max_price < max_price+1; curr_max_price++)
        if (prices[0] <= curr_max_price)
            dp[0][curr_max_price] = pages[0];

    for (int i = 1; i < N; i++) {
        for (int curr_max_price = 0; curr_max_price < max_price+1; curr_max_price++) {
            int a = 0;
            if (curr_max_price >= prices[i] && curr_max_price - prices[i] >= 0)
                a = pages[i] + dp[i-1][curr_max_price - prices[i]];
            int b = dp[i-1][curr_max_price];
            dp[i][curr_max_price] = max(a, b);
        }
    }

    cout << dp[N-1][max_price];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int>> cache;

int dfs(int i, int curr_price, vector<int>& prices, vector<int>& pages, int N, int max_price) {
    if (i == N)
        return 0;
    if (cache[i][curr_price] != -1)
        return cache[i][curr_price];

    int a_pages = INT_MIN;
    if (curr_price + prices[i] <= max_price)
        a_pages = pages[i] + dfs(i+1, curr_price + prices[i], prices, pages, N, max_price);
    
    int b_pages = dfs(i+1, curr_price, prices, pages, N, max_price);

    return cache[i][curr_price] = max(a_pages, b_pages);
}

void solve_recursively(vector<int>& prices, vector<int>& pages, int N, int max_price) {
    cache.assign(N, vector<int>(max_price + 1, -1));
    int max_pages = dfs(0, 0, prices, pages, N, max_price);
    cout << max_pages;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, max_price;
    cin >> N >> max_price;

    vector<int> prices(N);
    for (int i = 0; i < N; i++)
        cin >> prices[i];

    vector<int> pages(N);
    for (int i = 0; i < N; i++)
        cin >> pages[i];

    solve_iteratively(prices, pages, N, max_price);

    return 0;
}