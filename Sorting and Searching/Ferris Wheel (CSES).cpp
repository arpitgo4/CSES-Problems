// Ferris Wheel (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

void solve(vector<int>& W, int N, int MAX_W) {
    int count = 0;
    multiset<int> oms(W.begin(), W.end());

    while (oms.size() > 1) {
        multiset<int>::iterator itr1 = oms.begin();
        oms.erase(itr1);

        int diff = MAX_W - *itr1;
        multiset<int>::iterator itr2 = oms.upper_bound(diff);

        // no need to check for size, because while loop is making sure we have atleast 2 elements in the set
        // check if element found is not the only element in the set, in other words there are no other elements available in the set
        if (itr2 == oms.end() || itr2 != oms.begin())                  
            oms.erase(prev(itr2));

        count++;
    }

    if (oms.size() != 0)
        count++;

    cout << count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, MAX_W;
    cin >> N >> MAX_W;

    vector<int> W(N);
    for (int i = 0; i < N; i++)
        cin >> W[i];

    solve(W, N, MAX_W);

    return 0;
}