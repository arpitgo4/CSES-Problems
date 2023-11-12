// Ferris Wheel (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;
using ll = long long;

// Time: O(NlogN)
// Space: O(N)

void solve(vector<ll>& W, int N, ll MAX_W) {
    ll count = 0;
    multiset<ll> oSet(W.begin(), W.end());

    while (!oSet.empty()) {
        set<ll>::iterator itr1 = oSet.begin();
        oSet.erase(itr1);
        count++;

        if (oSet.size() == 0)
            continue;

        ll diff = MAX_W - *itr1;
        set<ll>::iterator itr2 = oSet.lower_bound(diff);
        if (itr2 == oSet.end())
            itr2 = prev(itr2);

        if (*itr2 <= diff)
            oSet.erase(itr2);
    }

    cout << count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; ll MAX_W;
    cin >> N >> MAX_W;

    vector<ll> W(N);
    for (int i = 0; i < N; i++)
        cin >> W[i];

    solve(W, N, MAX_W);

    return 0;
}