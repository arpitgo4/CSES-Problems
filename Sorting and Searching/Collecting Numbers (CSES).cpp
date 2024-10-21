// Collecting Numbers (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N)
// Space: O(N)

/**
 * each number will have edge to the next number
 * in increasing ordeer
 * 
 * count of back-edges for the given list is the 
 * number of rounds that will be required to
 * collect all numbers in increasing order
 */

void solve(vector<int>& A, int N) {
    vector<int> table(N+1, -1);
    for (int i = 0; i < N; i++)
        table[A[i]] = i;

    int count = 1;
    for (int x = 2; x <= N; x++) {
        if (table[x] < table[x-1])
            count++;
    }

    cout << count << endl;
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