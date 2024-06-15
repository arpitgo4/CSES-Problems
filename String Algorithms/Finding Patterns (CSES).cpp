// Finding Patterns (CSES)
 
#include <iostream>
#include <vector>
#include <string>
 
using namespace std;

// Time: O(M + N)
// Space: O(M)

const int MAX_N = 1e6;
const int ALPHABET = 26;

vector<bool> match;
vector<vector<int>> T;
vector<bool> visited;

int node_counter = 0;

class TrieNode {
public:
    int node_id;
    vector<int> word_indices;
    bool is_word;
    vector<TrieNode*> next;
    char par_ch;
    vector<TrieNode*> go;
    TrieNode* parent;
    TrieNode* link;
    TrieNode* exit_link;

    TrieNode() {
        this->node_id = ++node_counter;
        this->is_word = false;
        this->next.assign(ALPHABET, NULL);
        this->go.assign(ALPHABET, NULL);
        this->parent = NULL;
        this->link = NULL;
        this->exit_link = NULL;
        this->par_ch = '$';
        this->word_indices = vector<int>();
    }

    TrieNode(char par_ch, TrieNode* parent) : TrieNode() {
        this->parent = parent;
        this->par_ch = par_ch;
    }
}root;

vector<TrieNode*> nodes;

void insert_trie(string& S, int pattern_idx) {
    TrieNode* node = &root;
    for (char c : S) {
        int i = c - 'a';
        if (node->next[i] == NULL)
            node->next[i] = new TrieNode(c, node);
        node = node->next[i];
        nodes[node->node_id] = node;
    }

    node->is_word = true;
    node->word_indices.push_back(pattern_idx);
}

TrieNode* go(TrieNode* node, char ch);

TrieNode* get_link(TrieNode* node) {
    if (node->link == NULL) {
        if (node == &root || node->parent == &root) {
            node->link = &root;
        } else {
            TrieNode* link = get_link(node->parent);
            node->link = go(link, node->par_ch);
        }
    }
    
    return node->link;
}

TrieNode* go(TrieNode* node, char ch) {
    int i = ch - 'a';
    if (node->go[i] == NULL) {
        if (node->next[i] != NULL)
            node->go[i] = node->next[i];
        else 
            node->go[i] = (node == &root) ? &root : go(get_link(node), ch);
    }

    return node->go[i];
}

bool dfs(int u, int p) {
    bool found = visited[nodes[u]->node_id];
    for (int v : T[u]) {
        if (v != p)
            found = dfs(v, u) || found;
    }

    if (nodes[u]->is_word && found) {
        for (int word_idx : nodes[u]->word_indices)
            match[word_idx] = true;
    }

    return found;
}

void solve(string& text, vector<string>& patterns, int K) {
    T.assign(MAX_N, vector<int>());
    nodes.assign(MAX_N, NULL);
    visited.assign(MAX_N, false);
    match.assign(K, false);
    for (int i = 0; i < K; i++)
        insert_trie(patterns[i], i);

    nodes[root.node_id] = &root;

    // build suffix links for all nodes in trie
    for (int i = 1; i <= node_counter; i++) {
        TrieNode* node = nodes[i];
        TrieNode* link = get_link(node);

        // add each suffix link as edge in suffix link tree
        T[node->node_id].push_back(link->node_id);
        T[link->node_id].push_back(node->node_id);
    }

    TrieNode* node = &root;
    for (char c : text) {
        node = go(node, c);
        visited[node->node_id] = true;
    }

    dfs(root.node_id, -1);

    for (bool found : match)
        cout << (found ? "YES" : "NO") << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string T;
    getline(cin, T);

    int K;
    cin >> K;

    string buf;
    getline(cin, buf);
    vector<string> patterns(K);
    for (int i = 0; i < K; i++)
        getline(cin, patterns[i]);

    solve(T, patterns, K);
    
    return 0;
}