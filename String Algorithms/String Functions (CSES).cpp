// String Functions (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
vector<int> Z, pi;

void z_function(string& S) {
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

void prefix_function(string& S) {
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

void solve(string& S) {
    z_function(S);
    prefix_function(S);

    for (int v : Z)
        cout << v << " ";
    cout << endl;

    for (int v : pi)
        cout << v << " ";
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);
    
    return 0;
}