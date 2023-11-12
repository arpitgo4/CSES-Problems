// Concert Tickets (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

void solve(vector<int>& prices, vector<int>& customer_prices, int N, int M) {
    multiset<int> oSet(prices.begin(), prices.end());

    for (int c_price : customer_prices) {
        int res = -1;
        auto itr = oSet.lower_bound(c_price);
        if (oSet.size() == 0) {
            res = -1;
        }
        else if (itr == oSet.begin()) {
            if (*itr <= c_price) {
                res = *itr;
                oSet.erase(itr);
            }
        } else if (itr == oSet.end()) {
            itr = prev(itr);
            res = *itr;
            oSet.erase(itr);
        } else {
            if (*itr > c_price)
                itr = prev(itr);

            res = *itr;
            oSet.erase(itr);
        }

        cout << res << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<int> prices(N);
    for (int i = 0; i < N; i++)
        cin >> prices[i];

    vector<int> customer_prices(M);
    for (int i = 0; i < M; i++)
        cin >> customer_prices[i];

    solve(prices, customer_prices, N, M);

    return 0;
}