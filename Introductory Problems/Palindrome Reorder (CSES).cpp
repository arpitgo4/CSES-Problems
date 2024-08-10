// Palindrome Reorder (CSES)
 
#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
// Time: O(N)
// Space: O(1)
 
void solve(string& S) {
    vector<int> table(26, 0);
    for (char c : S)
        table[c - 'A']++;

    int odd_count = 0;
    for (int a : table)
        if (a % 2 == 1)
            odd_count++;

    if (odd_count > 1) {
        cout << "NO SOLUTION" << endl;
        return;
    } 

    int N = S.length();
    int l = 0, h = N-1;
    for (int i = 0; i < 26; i++) {
        int count = table[i];
        char c = i + 'A';

        if (count % 2 == 1) {
            S[N/2] = c;
            count--;
        }

        while (count > 0) {
            S[l] = S[h] = c;
            l++; h--;
            count -= 2;
        }
    } 
    
    cout << S << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    getline(cin, S);

    solve(S);
    
    return 0;
}