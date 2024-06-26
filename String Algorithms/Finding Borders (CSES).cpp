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

void print_borders_iterative(string& S) {
    vector<int> borders;
    int N = S.length(), j = pi[N-1];
    while (j > 0) {
        borders.push_back(j);
        j = pi[j-1];
    }

    reverse(borders.begin(), borders.end());

    for (int l : borders)
        cout << l << " ";
}

void print_borders(int pi_val) {
    if (pi_val > 0) {
        print_borders(pi[pi_val-1]);
        cout << pi_val << " ";
    }
}

void solve(string& S) {
    string str = S + '$';
    pi_function(str);

    int N = S.length();

    // print_borders_iterative(S);
    print_borders(pi[N-1]);

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