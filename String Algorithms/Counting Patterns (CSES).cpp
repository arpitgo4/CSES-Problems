// Counting Patterns (CSES)
 
#include <iostream>
#include <vector>
#include <string>
 
using namespace std;

// Time: O(N + M)
// Space: O(M)
 
const int ALPHABET = 26;
vector<int> pattern_count;

class TrieNode {
public:
    bool is_word;
    vector<int> word_indices;
    vector<TrieNode*> next;
    vector<TrieNode*> go;
    TrieNode* link;
    TrieNode* exit_link;
    char par_ch;
    TrieNode* parent;

    TrieNode() {
        this->next.assign(ALPHABET, NULL);
        this->go.assign(ALPHABET, NULL);
        this->is_word = false;
        this->link = NULL;
        this->exit_link = NULL;
        this->parent = NULL;
    }

    TrieNode(TrieNode* parent, char par_ch) : TrieNode() {
        this->par_ch = par_ch;
        this->parent = parent;
    }
}root;

void insert_trie(string& S, int pat_index) {
    TrieNode* node = &root;
    for (char c : S) {
        int i = c - 'a';
        if (node->next[i] == NULL)
            node->next[i] = new TrieNode(node, c);
        node = node->next[i];
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
/**
 * Exit link, is the closest suffix link which ends in a word
*/
TrieNode* get_exit_link(TrieNode* node) {
    if (node->exit_link == NULL) {
        TrieNode* link = get_link(node);
        if (link == &root || link->is_word)
            node->exit_link = link;
        else node->exit_link = get_exit_link(link);
    }

    return node->exit_link;
}

void solve(string& T, vector<string>& patterns, int K) {
    pattern_count.assign(K, 0);
    for (int i = 0; i < K; i++)
        insert_trie(patterns[i], i);

    TrieNode* node = &root;
    for (char c : T) {
        node = go(node, c);

        // calculate and memoize all the exit links for all nodes traversed
        // in the automata
        TrieNode* word_node = node;
        while (word_node != &root) {
            for (int idx : word_node->word_indices)
                pattern_count[idx]++;

            word_node = get_exit_link(word_node);
        }
    }

    for (int count : pattern_count)
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