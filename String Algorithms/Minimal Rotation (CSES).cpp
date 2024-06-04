// Minimal Rotation (CSES)

#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
/**
 * Remanents of Suffix Array implementation
 * 
 * P[i] => represents suffix (starting index for substring[i..N])
 * C[i] => represents equivalence class for the suffix index stored at ith location
 * C[P[i]] => represents equivalence class for the suffix, P[i]
 * 
 * C[P[i]] => Suffix.equivalence_class
 * 
 * With Object-oriented programming,
 * we go deeper into object properties with `.` notation and we go deeper into object
 * when our statement reads from left to right or outside in.
 * 
 * But, with Procedural programming,
 * we go deeper into supposed to be object by `[]` notation and we go deeper into object
 * when our statement reads from right to left or inside out.
*/

// Time: O(N)
// Space: O(N)

/**
 * Booth's Algorithm
 * 
 * Function to find the lexicographically minimal rotation
 * of a string
*/
int find_min_rotation(string s)
{
    // Concatenate string to itself to avoid modular arithmetic
    s += s;

    // Initialize failure function
    vector<int> failureFunc(s.size(), -1);

    // Initialize least rotation of string found so far
    int minRotationIdx = 0;

    // Iterate over the concatenated string
    for (int currentIdx = 1; currentIdx < s.size();
         ++currentIdx) {
        char currentChar = s[currentIdx];
        int failureIdx
            = failureFunc[currentIdx - minRotationIdx - 1];

        // Find the failure function value
        while (
            failureIdx != -1
            && currentChar
                   != s[minRotationIdx + failureIdx + 1]) {
            if (currentChar
                < s[minRotationIdx + failureIdx + 1]) {
                minRotationIdx
                    = currentIdx - failureIdx - 1;
            }
            failureIdx = failureFunc[failureIdx];
        }

        // Update the failure function and the minimum rotation index
        if (currentChar
            != s[minRotationIdx + failureIdx + 1]) {
            if (currentChar < s[minRotationIdx]) {
                minRotationIdx = currentIdx;
            }
            failureFunc[currentIdx - minRotationIdx] = -1;
        }
        else {
            failureFunc[currentIdx - minRotationIdx]
                = failureIdx + 1;
        }
    }

    // Return the index of the lexicographically minimal rotation
    return minRotationIdx;
}

void solve(string& S) {
    int min_rotation_idx = find_min_rotation(S);

    int N = S.length();
    for (int i = 0; i < N; i++)
        cout << S[(min_rotation_idx + i) % N];
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    getline(cin, S);

    solve(S);
    
    return 0;
}