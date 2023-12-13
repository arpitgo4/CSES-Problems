// Finding Borders (CSES)

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

// Time: O(N)
// Space: O(N)

// TODO: Add a second hash to drastically lower hash-collision probability 

const ll P = 31;
const ll MOD = 1e9 + 9;
vector<ll> POW;
vector<ll> HASH;


void init(string& S, int N) {
    POW.assign(N, 1);
    HASH.assign(N, 0);

    HASH[0] = S[0] - 'a' + 1;
    for (int i = 1; i < N; i++) {
        POW[i] = (POW[i-1] * P) % MOD;
        HASH[i] = ((((S[i] - 'a' + 1) * POW[i]) + HASH[i-1]) % MOD) % MOD;
    }
}

ll compute_hash(int lo, int hi) {
    if (lo == 0)
        return HASH[hi];    

    return (HASH[hi] - HASH[lo-1] + MOD) % MOD;
}

bool compare_substrings(int l1, int h1, int l2, int h2) {
    ll H1 = compute_hash(l1, h1);
    ll H2 = compute_hash(l2, h2);

    ll normalized_H1 = (H1 * POW[h2-h1]) % MOD;         // equalizing hashes by equalizing difference between max powers

    return normalized_H1 == H2;
}

void solve(string& S) {
    int N = S.length();
    init(S, N);

    for (int i = 0; i < N-1; i++) {
        if (compare_substrings(0, i, N-1-i, N-1))
            cout << i+1 << " ";
    }
}

// Time: O(N^2)
// Space: O(1)
void solve_brute(string& S) {
    int N = S.length();

    vector<int> borders;

    for (int i = 0; i < N-1; i++) {
        int j = N-1-i;
        int k = 0;
        while (k <= i && S[k] == S[j]) {
            j++;
            k++;
        }

        if (k-1 == i)
            borders.push_back(i+1);
    }

    for (int b : borders)
        cout << b << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    cin >> S;

    // solve_brute(S);
    solve(S);

    return 0;
}