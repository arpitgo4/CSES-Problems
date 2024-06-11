// Finding Patterns (CSES)
 
#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
/**
 * Needs BFS based construction to pass all test cases
 * 
 * Reduce number of nodes in Trie by compressing redundant nodes-edges
*/

// Time: O(M + N)
// Space: O(M)

const int ALPHABET = 26;
vector<bool> found;

class TrieNode {
public:
    vector<int> word_idx;
    bool is_word;
    vector<TrieNode*> next;
    char par_ch;
    vector<TrieNode*> go;
    TrieNode* parent;
    TrieNode* link;
    TrieNode* exit_link;

    TrieNode() {
        this->is_word = false;
        this->next.assign(ALPHABET, NULL);
        this->go.assign(ALPHABET, NULL);
        this->parent = NULL;
        this->link = NULL;
        this->exit_link = NULL;
        this->par_ch = '$';
        this->word_idx = vector<int>();
    }

    TrieNode(char par_ch, TrieNode* parent) : TrieNode() {
        this->parent = parent;
        this->par_ch = par_ch;
    }
}root;

void insert_trie(string& S, int pattern_idx) {
    TrieNode* node = &root;
    for (char c : S) {
        int i = c - 'a';
        if (node->next[i] == NULL)
            node->next[i] = new TrieNode(c, node);
        node = node->next[i];
    }

    node->is_word = true;
    node->word_idx.push_back(pattern_idx);
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

TrieNode* get_exit_link(TrieNode* node) {
    if (node == &root)
        return &root;
    if (node->exit_link != NULL)
        return node->exit_link;
    
    TrieNode* link = get_link(node);
    if (link->is_word)
        return node->exit_link = link;
    else return node->exit_link = get_exit_link(link);
}

void output_vertex(TrieNode* node) {
    while (node != &root) {
        if (node->is_word) {
            for (int idx : node->word_idx)
                found[idx] = true;
        }

        node = get_exit_link(node);
    }
}

void solve(string& T, vector<string>& patterns, int K) {
    found.assign(K, false);
    for (int i = 0; i < K; i++)
        insert_trie(patterns[i], i);

    TrieNode* node = &root;
    for (char c : T) {
        node = go(node, c);
        output_vertex(node);
    }

    for (bool match : found)
        cout << (match ? "YES" : "NO") << endl;
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