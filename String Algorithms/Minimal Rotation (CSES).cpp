// Minimal Rotation (CSES)

#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
/**
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

// Time: O(NlogN)
// Space: O(N)

vector<int> SA;

void sort_cyclic_shifts(string& S) {
    const int ALPHABET = 256;
    int N = S.length();
    SA.assign(N, 0);
    vector<int> cnt(max(ALPHABET, N), 0);
    for (int i = 0; i < N; i++)
        cnt[S[i]]++;
    for (int i = 1; i < ALPHABET; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < N; i++)
        SA[--cnt[S[i]]] = i;

    vector<int> C(N, 0);
    C[SA[0]] = 0;
    int classes = 1;
    for (int i = 1; i < N; i++) {
        if (S[SA[i]] != S[SA[i-1]])
            classes++;
        C[SA[i]] = classes - 1;
    }

    vector<int> SAN(N), CN(N);
    for (int h = 0; (1 << h) < N; ++h) {
        for (int i = 0; i < N; i++) {
            SAN[i] = SA[i] - (1 << h);
            if (SAN[i] < 0)
                SAN[i] += N;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < N; i++)
            cnt[C[SAN[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = N-1; i >= 0; i--)
            SA[--cnt[C[SAN[i]]]] = SAN[i];
        CN[SA[0]] = 0;
        classes = 1;
        for (int i = 1; i < N; i++) {
            pair<int, int> cur = {C[SA[i]], C[(SA[i] + (1 << h)) % N]};
            pair<int, int> prev = {C[SA[i-1]], C[(SA[i-1] + (1 << h)) % N]};
            if (cur.first != prev.first || cur.second != prev.second)
                ++classes;
            CN[SA[i]] = classes - 1;
        }
        C = CN;
    }
}

void solve(string& S) {
    sort_cyclic_shifts(S);

    int suff_idx = SA[0];
    int N = S.length();
    for (int i = 0; i < N; i++)
        cout << S[(suff_idx+i) % N];
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