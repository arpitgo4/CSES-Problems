// Collecting Numbers (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Time: O(N)
// Space: O(1)

// numbers range [1, N]
// can sort in O(N), O(1)

// 4 2 1 5 3
// s d d u d
// 

void solve(vector<int>& A, int N) {

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