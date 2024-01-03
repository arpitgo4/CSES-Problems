// Increasing Array (CSES)

#include <iostream>

using namespace std;
using ll = long long;

// Time: O(N)
// Space: O(1)

// greedy approach
// if A[i-1] > A[i], then, just add the diff of two numbers in A[i] 
// (min number of moves to satisfy the problem constraint)
void solve(vector<ll>& A, int N) {
    ll moves = 0;
    for (int i = 1; i < N; i++) {
        if (A[i-1] > A[i]) {
            ll diff = A[i-1] - A[i];
            moves += diff;
            A[i] += diff;
        }
    }

    cout << moves;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N);

    return 0;
}