// Towers (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

void solve(vector<int>& A, int N) {
    multiset<int> uSet;
    for (int i = 0; i < N; i++) {
        auto itr = uSet.upper_bound(A[i]);
        if (itr != uSet.end())
            uSet.erase(itr);

        uSet.insert(A[i]);
    }

    cout << uSet.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N);

    return 0;
}