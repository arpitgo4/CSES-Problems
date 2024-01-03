// Elevator Rides (CSES)

#include <iostream>
#include <vector>

using namespace std;

/**
 * Try out all possible permutations of people and calculate number of elevator rides for each one.
 * Return the minimum elevator ride count among all possible permutations.
 * 
 * Number of permutations = N!
 * Time to calculate no. of rides = O(N)
*/

// Time: O(N * N!) ~ O(N!)
// Space: O(N)

// Time: O(2^N)
// Space: O(2^N)

vector<vector<int>> cache;

int dfs(int i, int mask) {

}

void solve(vector<int>& A, int N, int MAX_W) {
    cache.assign();

    int count = dfs(0, (1 << ??) - 1);

    cout << count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, MAX_W;
    cin >> N >> MAX_W;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N, MAX_W);

    return 0;
}