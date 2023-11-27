// String Matching (CSES)

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Time: O(N + M)
// Space: O(N + M)


vector<int> Z;

void fill_Z_array(string& S) {
    int N = S.length();
    Z.assign(N, 0);

    int l = 0, r = 0;
    for (int i = 1; i < N; i++) {
        if (i < r)
            Z[i] = min(r-i, Z[i-l]);
        while (i + Z[i] < N && S[Z[i]] == S[i + Z[i]])
            Z[i]++;
        if (i + Z[i] > r) {
            l = i;
            r = i + Z[i];
        }
    }
}

void solve(string& T, string& P) {
    int M = P.length();

    string z_string = P + '$' + T;
    fill_Z_array(z_string);

    int X = z_string.length();
    int counter = 0;
    for (int i = 0; i < X; i++)
        if (Z[i] == M)
            counter++;

    cout << counter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string T, P;
    cin >> T >> P;

    solve(T, P);

    return 0;
}