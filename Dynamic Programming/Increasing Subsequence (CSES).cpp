// Increasing Subsequence (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N^2)
// Space: O(N)

vector<int> cache;

int dfs(int i, vector<int>& A, int N) {
    if (i == N)
        return 0;
    if (cache[i] != -1)
        return cache[i];

    int count = 1;
    for (int j = i+1; j < N; j++) {
        if (A[j] > A[i])
            count = max(count, 1 + dfs(j, A, N));
    }

    return cache[i] = count;
}

void solve(vector<int>& A, int N) {
    cache.assign(N, -1);

    int max_len = 1;
    for (int i = 0; i < N; i++)
        max_len = max(max_len, dfs(i, A, N));
    
    cout << max_len << endl;
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