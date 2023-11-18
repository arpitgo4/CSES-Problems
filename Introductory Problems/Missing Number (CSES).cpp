// Missing Number (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// Time: O(N)
// Space: O(1)

// bit manipulation
void solve2(vector<int>& A, int N) {
    int x = 0;
    for (int a = 1; a <= N; a++)
        x ^= a;
    for (int a : A)
        x ^= a;

    cout << x;
}

// cycle sort
void solve(vector<int>& A, int N) {
    int missing_number = N;
    for (int i = 0; i < N-1; i++) {
        int corr_idx = A[i]-1;
        while (corr_idx >= 0 && corr_idx < N-1 && corr_idx != i) {
            swap(A[i], A[corr_idx]);
            corr_idx = A[i]-1;
        }
    }

    for (int i = 0; i < N-1; i++) {
        int corr_idx = A[i]-1;
        if (corr_idx != i) {
            missing_number = i+1;
            break;
        }
    }

    cout << missing_number;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> A(N-1);
    for (int i = 0; i < N-1; i++)
        cin >> A[i];

    // solve(A, N);
    solve2(A, N);

    return 0;
}