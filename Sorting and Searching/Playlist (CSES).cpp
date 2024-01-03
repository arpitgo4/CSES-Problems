// Playlist (CSES)

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

/**
 * Note: Using unordered_map gives TLE. Although, time complexity is O(N) in that case. But hashing and collisions on big
 * datasets increases the runtime
*/

void solve(vector<int>& A, int N) {
    int max_len = INT_MIN;
    int j = 0;
    map<int,int> oMap;
    for (int i = 0; i < N; i++) {
        if (oMap.find(A[i]) != oMap.end() && oMap[A[i]] >= j)
            j = oMap[A[i]] + 1;

        oMap[A[i]] = i;
        max_len = max(max_len, i-j+1);
    }

    cout << max_len;
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