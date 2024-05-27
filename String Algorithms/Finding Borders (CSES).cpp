// Finding Borders (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
/**
 * After finding border for whole string S with prefix function (pi)
 * subsequent borders can be found by looking for border within the previous border
 * i.e next border will the border of the previous border
 * pi[pi[i-1]].... recursive pi of pi of pi....
 * 
 * TODO: write recursive implementation for the above
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
    string str = S + '$';
    pi_function(str);

    vector<int> borders;
    int N = S.length(), j = pi[N-1];
    while (j > 0) {
        borders.push_back(j);
        j = pi[j-1];
    }

    reverse(borders.begin(), borders.end());

    for (int l : borders)
        cout << l << " ";
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