// Repetitions (CSES)

#include <iostream>

using namespace std;

// Time: O(N)
// Space: O(1)

void solve(string& S) {
    int N = S.length();
    int max_rep = 1;
    int rep_counter = 1;
    for (int i = 1; i < N; i++) {
        if (S[i-1] == S[i])
            rep_counter++;
        else rep_counter = 1;

        max_rep = max(max_rep, rep_counter);
    }

    cout << max_rep;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    cin >> S;

    solve(S);

    return 0;
}