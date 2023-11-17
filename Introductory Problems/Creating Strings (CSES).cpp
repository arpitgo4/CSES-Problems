// Creating Strings (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> VIS;
vector<string> res;

void dfs(string& S, string& acc) {
    if (acc.size() == S.length()) {
        res.push_back(acc);
        return;
    }

    int last_char = 0;
    for (int i = 0; i < S.length(); i++) {
        if (VIS[i] == 0 && last_char != S[i]) {
            VIS[i] = 1;
            acc.push_back(S[i]);
            last_char = S[i];
            dfs(S, acc);
            acc.pop_back();
            VIS[i] = 0;
        }
    }
}

void solve(string& S) {
    int N = S.length();

    VIS.assign(N, 0);
    sort(S.begin(), S.end());

    string acc = "";
    dfs(S, acc);

    cout << res.size() << endl;
    for (string& s : res)
        cout << s << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    cin >> S;

    solve(S);

    return 0;
}