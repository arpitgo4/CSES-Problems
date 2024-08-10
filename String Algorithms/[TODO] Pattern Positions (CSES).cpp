// Pattern Positions (CSES)
 
#include <iostream>
#include <vector>
#include <string>
#include <climits>
 
using namespace std;
 
// Time: O(N + M)
// Space: O(M)
 
const int MAX_N = 1e6;
const int ALPHABET = 26;

vector<vector<int>> T;                      // suffix-link tree
vector<bool> visited;
vector<int> pattern_pos;

int node_counter = 0;

class TrieNode {
public:
    int node_id;
    bool is_word;
    int word_len;
    vector<TrieNode*> next;
    vector<TrieNode*> go;
    TrieNode* link;
    TrieNode* parent;
    char par_ch;
    vector<int> word_indices;
    int text_idx;
    int depth;

    TrieNode() {
        this->node_id = ++node_counter;
        this->is_word = false;
        this->word_len = 0;
        this->next.assign(ALPHABET, NULL);
        this->go.assign(ALPHABET, NULL);
        this->link = NULL;
        this->parent = NULL;
        this->par_ch = '$';
        this->word_indices = vector<int>();
        this->text_idx = INT_MAX;
        this->depth = 0;
    }

    TrieNode(TrieNode* parent, char par_ch, int depth) : TrieNode() {
        this->parent = parent;
        this->par_ch = par_ch;
        this->depth = depth;
    }
}root;

vector<TrieNode*> nodes;

void insert_trie(string& S, int pat_idx) {
    TrieNode* node = &root;
    for (char c : S) {
        int i = c - 'a';
        if (node->next[i] == NULL)
            node->next[i] = new TrieNode(node, c, node->depth+1);

        node = node->next[i];
        nodes[node->node_id] = node;
    }

    node->is_word = true;
    node->word_indices.push_back(pat_idx);
    node->word_len = S.length();
}

TrieNode* go(TrieNode* node, char c);

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

TrieNode* go(TrieNode* node, char c) {
    int i = c - 'a';
    if (node->go[i] == NULL) {
        if (node->next[i] != NULL)
            node->go[i] = node->next[i];
        else {
            TrieNode* link = get_link(node);
            node->go[i] = (node == &root) ? &root : go(link, c);
        }
    }

    return node->go[i];
}

// percolate text_indices for all nodes in the suffix link tree
void dfs1(int u, int p) {
    int text_idx_u = nodes[u]->text_idx;
    int u_depth = nodes[u]->depth;
    for (int v : T[u]) {
        if (v != p) {
            int v_depth = nodes[v]->depth;
            int text_idx_v = text_idx_u + v_depth - u_depth;
            nodes[v]->text_idx = min(nodes[v]->text_idx, text_idx_v);

            dfs1(v, u);
        }
    }
}

bool dfs(int u, int p) {
    bool found = visited[u];
    for (int v : T[u]) {
        if (v != p) {
            found = dfs(v, u) || found;
        }
    }

    if (nodes[u]->is_word && found) {
        for (int word_idx : nodes[u]->word_indices)
            pattern_pos[word_idx] = min(pattern_pos[word_idx], nodes[u]->text_idx);
    }

    return found;
}

void solve(string& text, vector<string>& patterns, int K) {
    T.assign(MAX_N, vector<int>());
    nodes.assign(MAX_N, NULL);
    visited.assign(MAX_N, false);
    pattern_pos.assign(K, INT_MAX);

    for (int i = 0; i < K; i++)
        insert_trie(patterns[i], i);

    nodes[root.node_id] = &root;

    for (int i = 1; i <= node_counter; i++) {
        TrieNode* node = nodes[i];
        TrieNode* link = get_link(node);

        T[node->node_id].push_back(link->node_id);
        T[link->node_id].push_back(node->node_id);
    }

    int N = text.length();
    TrieNode* node = &root;
    for (int i = 0; i < N; i++) {
        node = go(node, text[i]);
        node->text_idx = min(node->text_idx, i);
        visited[node->node_id];
    }

    dfs1(root.node_id, -1);

    for (int i = 1; i <= node_counter; i++) {
        cout << node->par_ch << ": " << node->text_idx << endl;
    }

    dfs(root.node_id, -1);

    for (int i : pattern_pos)
        cout << (i == INT_MAX ? -1 : i) << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string text;
    getline(cin, text);

    int K;
    cin >> K;

    string buf;
    getline(cin, buf);
    vector<string> patterns(K);
    for (int i = 0; i < K; i++)
        getline(cin, patterns[i]);

    solve(text, patterns, K);
    
    return 0;
}