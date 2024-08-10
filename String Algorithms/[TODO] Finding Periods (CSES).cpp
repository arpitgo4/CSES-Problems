// Finding Periods (CSES)

#include <iostream>
#include <vector>
 
using namespace std;
 
/**
 * Whole string can be the period of the given string
 * 
 * If I can make the S from it's prefix which is period for S,
 * find the period for period of S
 * 
 * Above process can be repeated recursively and we will get all 
 * the periods
*/

// Time: O(N)
// Space: O(N)
 
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

void solve(string& S) {
    int N = S.length();

    string str = S + '$';
    pi_function(str);

    cout << pi[N-1] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    cin >> S;

    solve(S);

    return 0;
}