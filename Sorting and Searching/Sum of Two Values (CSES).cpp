// Sum of Two Values (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

void solve(vector<int>& A, int N, int K) {
    vector<pair<int,int>> D(N);
    for (int i = 0; i < N; i++)
        D[i] = { A[i], i };

    sort(D.begin(), D.end());
    int l = 0, h = N-1;
    while (l < h) {
        int sum = D[l].first + D[h].first;
        if (sum == K) {
            cout << D[l].second+1 << " " << D[h].second+1 << endl;
            return;
        } else if (sum < K)
            l++;
        else h--;
    }

    cout << "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N, K);

    return 0;
}