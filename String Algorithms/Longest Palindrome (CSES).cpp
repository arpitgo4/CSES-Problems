// Longest Palindrome (CSES)
 
#include <iostream>
 
using namespace std;
 
// Time: O(N^2)
// Space: O(1)
string longest_palindromic_substring(string& S, int N) {
    return "";
}

void solve(string& S) {
    int N = S.length();

    cout << longest_palindromic_substring(S, N);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);
    
    return 0;
}