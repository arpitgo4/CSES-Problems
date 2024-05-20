// String Matching (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N + M)
// Space: O(N + M)

vector<int> pi;

void prefix_function(string& T) {
    int N = T.length();
    pi.assign(N, 0);
    for (int i = 1; i < N; i++) {
        int j = pi[i-1];
        while (j > 0 && T[i] != T[j])
            j = pi[j-1];
        if (T[i] == T[j])
            j++;
        pi[i] = j;
    }
}

void solve(string& T, string& P) {
    int M = P.length();

    string str = P + '$' + T;
    prefix_function(str);
    
    int count = 0;
    for (int v : pi)
        if (v == M)
            count++;

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