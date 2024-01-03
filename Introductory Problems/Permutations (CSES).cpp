// Permutations (CSES)

#include <iostream>

using namespace std;

// Time: O(N)
// Space: O(1)

void solve(int N) {
    if (N == 1)
        cout << 1;
    else if (N <= 3)
        cout << "NO SOLUTION";
    else {
        for (int i = 2; i <= N; i+=2)
            cout << i << " ";
        for (int i = 1; i <= N; i+=2)
            cout << i << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    solve(N);

    return 0;
}