// Counting Patterns (CSES)
 
#include <iostream>
#include <vector>
#include <string>
 
using namespace std;

// Time: O(N + M)
// Space: O(M)

typedef long long ll;

const int MAX_N = 1e6;
const int ALPHABET = 26;

vector<ll> pattern_count;
vector<ll> cnt;
vector<vector<int>> T;

int node_counter = 0;

class TrieNode {
public:
    int node_id;
    bool is_word;
    vector<int> word_indices;
    vector<TrieNode*> next;
    vector<TrieNode*> go;
    TrieNode* link;
    char par_ch;
    TrieNode* parent;

    TrieNode() {
        this->node_id = ++node_counter;
        this->next.assign(ALPHABET, NULL);
        this->go.assign(ALPHABET, NULL);
        this->is_word = false;
        this->link = NULL;
        this->parent = NULL;
    }

    TrieNode(TrieNode* parent, char par_ch) : TrieNode() {
        this->par_ch = par_ch;
        this->parent = parent;
    }
}root;

vector<TrieNode*> nodes;

void insert_trie(string& S, int pat_index) {
    TrieNode* node = &root;
    for (char c : S) {
        int i = c - 'a';
        if (node->next[i] == NULL)
            node->next[i] = new TrieNode(node, c);
        node = node->next[i];
        nodes[node->node_id] = node;
    }

    node->is_word = true;
    node->word_indices.push_back(pat_index);
}

TrieNode* go(TrieNode* node, char ch);

/**
 * Suffix Link, is the longest proper suffix to the current prefix
*/
TrieNode* get_link(TrieNode* node) {
    if (node->link == NULL) {
        if (node == &root || node->parent == &root)
            node->link = &root;
        else {
            TrieNode* par_link = get_link(node->parent);
            node->link = go(par_link, node->par_ch);
        }
    }

    return node->link;
}

TrieNode* go(TrieNode* node, char ch) {
    int i = ch - 'a';
    if (node->go[i] == NULL) {
        if (node->next[i] != NULL)
            node->go[i] = node->next[i];
        else {
            TrieNode* link = get_link(node);
            if (link == &root)
                node->go[i] = &root;
            else node->go[i] = go(link, ch);
        }
    }

    return node->go[i];
}

ll dfs(int u, int p) {
    ll count = cnt[u];
    for (int v : T[u])
        if (v != p)
            count += dfs(v, u);

    if (nodes[u]->is_word) {
        for (int word_idx : nodes[u]->word_indices)
            pattern_count[word_idx] = count;
    }

    return count;
}

void solve(string& text, vector<string>& patterns, int K) {
    T.assign(MAX_N, vector<int>());
    pattern_count.assign(K, 0);
    cnt.assign(MAX_N, 0);
    nodes.assign(MAX_N, NULL);
    for (int i = 0; i < K; i++)
        insert_trie(patterns[i], i);

    nodes[root.node_id] = &root;

    // build suffix links for all nodes and suffix link tree
    for (int i = 1; i <= node_counter; i++) {
        TrieNode* node = nodes[i];
        TrieNode* link = get_link(node);

        T[node->node_id].push_back(link->node_id);
        T[link->node_id].push_back(node->node_id);
    }

    TrieNode* node = &root;
    for (char c : text) {
        node = go(node, c);
        cnt[node->node_id]++;
    }

    dfs(root.node_id, -1);

    for (ll count : pattern_count)
        cout << count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string T;
    getline(cin, T);

    int K;
    cin >> K;

    string buffer;
    getline(cin, buffer);
    vector<string> patterns(K);
    for (int i = 0; i < K; i++)
        getline(cin, patterns[i]);

    solve(T, patterns, K);
    
    return 0;
}