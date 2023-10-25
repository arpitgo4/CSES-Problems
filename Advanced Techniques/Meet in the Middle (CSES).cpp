// Meet in the Middle (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

// Time: O(2^(N/2)log(2^(N/2)))
// Space: O(2^(N/2))

void subset_dfs(vector<ll>& A, ll sum, int i, int h, vector<ll>& acc) {
    if (i > h) {
        acc.push_back(sum);
        return;
    }

    subset_dfs(A, sum, i+1, h, acc);
    subset_dfs(A, sum+A[i], i+1, h, acc);
}

void solve(vector<ll>& A, int k, int N) {
    int l = 0, h = N-1;
    int m = (h-l)/2 + l;

    vector<ll> sum_A;
    subset_dfs(A, 0, l, m, sum_A);

    vector<ll> sum_B;
    subset_dfs(A, 0, m+1, h, sum_B);
    sort(sum_B.begin(), sum_B.end());

    ll counter = 0;
    for (ll a : sum_A) {
        vector<ll>::iterator itr_lower = lower_bound(sum_B.begin(), sum_B.end(), k-a);
        vector<ll>::iterator itr_upper = upper_bound(sum_B.begin(), sum_B.end(), k-a);
        if (itr_lower != sum_B.end() && *itr_lower+a == k)
            counter += (prev(itr_upper)-itr_lower+1);
    }

    cout << counter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, k;
    cin >> N >> k;

    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, k, N);

    return 0;
}