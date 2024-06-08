// Distinct Substrings (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)
 
typedef long long ll;

vector<int> SA, LCP;

void build_suffix_array(string& S) {
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

void build_lcp_table(string& S) {
    int N = S.length();
    vector<int> rank(N, 0);
    for (int i = 0; i < N; i++)
        rank[SA[i]] = i;

    int k = 0;
    LCP.assign(N-1, 0);
    for (int i = 0; i < N; i++) {
        if (rank[i] == N-1) {
            k = 0;
            continue;
        }
        int j = SA[rank[i] + 1];
        while (i + k < N && j + k < N && S[i+k] == S[j+k])
            k++;
        LCP[rank[i]] = k;
        if (k)
            k--;
    }
}

void solve(string& S) {
    S += '$';
    build_suffix_array(S);
    build_lcp_table(S);

    int N = S.length();
    ll count = 0;
    for (int i = 1; i < N; i++)
        count += (N-SA[i]-1-LCP[i-1]);

    cout << count << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);
    
    return 0;
}