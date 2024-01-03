// Maximum Subarray Sum (CSES)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;
using ll = long long;

// Time: O(N)
// Space: O(1)

void solve(vector<ll>& A, int N) {
    ll max_sum = INT_MIN; ll sum = 0;
    int j = 0, i = 0;
    while (i < N) {
        sum += A[i];
        while (j < i && (sum < 0 || A[j] < 0)) {
            sum -= A[j];
            j++;
        }

        max_sum = max(max_sum, sum);
        i++;
    }

    cout << max_sum;
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