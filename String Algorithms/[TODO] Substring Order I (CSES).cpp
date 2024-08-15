// Substring Order I (CSES)
 
#include <iostream>
#include <vector>
#include <map>
 
using namespace std;
 
// Time: O(N + )
// Space: O(N)
 
const int MAXLEN = 100000;
int sz, last;

vector<int> vis;

struct state {
    int len, link;
    map<char, int> next;
};

state st[MAXLEN * 2];
int vis[MAXLEN * 2];

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void dfs(int u) {
    vis[u] = 1;
    
    for (auto& p : st[u].next) {
        char c = p.first;
        int v = p.second;
        if (vis[v] == 0) {
            dfs(v);
        }
    }
}

void solve(string& S, int K) {
    sa_init();
    for (char c : S)
        sa_extend(c);

    // st[0] => t0, root node for the suffix automaton
    // st{} => { map<char,int>, len, link }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    int K;
    cin >> K;

    solve(S, K);
    
    return 0;
}