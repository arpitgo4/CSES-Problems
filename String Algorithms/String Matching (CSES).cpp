// String Matching (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N + M)
// Space: O(M)

vector<int> pi;

void pi_function(string& S) {
    int N = S.length();
    pi.assign(N, 0);
    for (int i = 1; i < N; i++) {
        int j = pi[i-1];
        while (j > 0 && S[i] != S[j])
            j = pi[j-1];
        if (S[i] == S[j])
            j++;
        pi[i] = j;
    }
}

void solve(string& T, string& P) {
    int M = P.length();

    string str = P + '$';
    pi_function(str);
    
    int count = 0, prev_pi = 0;
    for (char c : T) {
        if (P[prev_pi] == c)
            prev_pi++;
        else {
            while (prev_pi > 0 && P[prev_pi] != c)
                prev_pi = pi[prev_pi-1];
            if (P[prev_pi] == c)
                prev_pi++;
        }

        if (prev_pi == M)
            count++;
    }

    cout << count << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string T, P;
    cin >> T >> P;

    solve(T, P);

    return 0;
}