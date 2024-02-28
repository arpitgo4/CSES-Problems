// Minimal Rotation (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;
using ll = long long;

// Time: O(NlogN)               // Rolling hash prefix + (least indices loop * longest common prefix binary search)
// Space: O(N)                  // prefix hash + least indices array

// brute-force, Time: O(N^2), Space: O(N^2)
// 1. Generate all rotations (O(N^2) => O(N) per possible rotation)
// 2a. Sort rotations array (O(N^2logN))
// 2b. Find lexico-lowest rotation from array (find 0th smallest number from array) (O(N^2))

// brute-force with trie, O(N^2)
// easier to implement than above quick-select search
// 1. Generate all rotations (O(N^2)) and push in trie (O(N^2))
// 2. Search lexico-lowest rotation from trie O(N^2)

// Rolling hash,
// lexico-lowest rotation must have smallest hash of all rotations

// NOTE: Rolling Hash will not work. Hashes can't be compared as they are built
// with modular arithmetic. Hash will recycle in a range and bigger hash
// can end up with smaller number

// O(N^2) algorithm with rolling hash,
// 1. find hash for all rotations and pick out the lowest hash

// O(N * (math for rolling hash)) algorithm with rolling hash?? [don't know the mod. math for this]
// 1. find hash for initial string taking i = 0, as the start
// 2. keep calculating rolling hash from initial hash taking i = [1, N] as start
// 3. find the lowest hash among above 

/**
 * Try finding smallest char location(s) in the given string O(N)
 * Compare each with binary search on prefix to check which one is greater O(logN)
 *     * Comparing prefixes in both strings with help of hashing in O(1)
 * Find the lexicographically minimal
 * 
 * Time: O(NlogN)
 * Space: O(N)              // hash prefix array + least indices array
*/

const ll P = 31;
const ll MOD = 1e9 + 7;
vector<ll> pref_hash, powers;

void compute_prefix_hash(string& S, int N) {
    powers.assign(N+1, 1);
    for (int i = 1; i < N+1; i++)
        powers[i] = P * powers[i-1] % MOD;

    pref_hash.assign(N+1, 0);
    for (int i = 1; i < N+1; i++) {
        ll c = S[i-1] - 'a';
        pref_hash[i] = (pref_hash[i-1] + (c * powers[i] % MOD)) % MOD;
    }
}

bool equal_substrings(int i, int j, int p, int q, int N) {
    ll hash1 = 0;
    if (j < N+1) {
        hash1 = (pref_hash[j] - pref_hash[i-1] + MOD) % MOD;
    } else {
        // overflowing first string
        hash1 = (pref_hash[N] - pref_hash[i-1] + MOD) % MOD;
        ll prefix_hash_1 = pref_hash[j % (N+1)];
        hash1 = (hash1 * powers[(j % (N+1))] % MOD + prefix_hash_1 + MOD) % MOD;
    }

    ll hash2 = 0;
    if (q < N+1) {
        hash2 = (pref_hash[q] - pref_hash[p-1] + MOD) % MOD;
    } else {
        // overflowing second string
        hash2 = (pref_hash[N] - pref_hash[p-1] + MOD) % MOD;
        ll prefix_hash_2 = pref_hash[q % (N+1)];
        hash2 = (hash2 * powers[(q % (N+1))] % MOD + prefix_hash_2 + MOD) % MOD;
    }

    hash1 = hash1 * powers[p-i] % MOD;

    return hash1 == hash2;
}

vector<int> least_char_indices(string& S, int N) {
    vector<int> freq(26, 0);
    for (char c : S)
        freq[c - 'a']++;

    char least_char = '$';
    for (int i = 0; i < 26; i++)
        if (freq[i] > 0) {
            least_char = i + 'a';
            break;
        }

    vector<int> indices;
    for (int i = 0; i < N; i++)
        if (S[i] == least_char)
            indices.push_back(i);

    return indices;
}

void print_rotation(string& S, int N, int idx) {
    int i = idx;
    do {
        cout << S[i++];
        i %= N;
    } while (i != idx);
}

// Shadow Binary Search
int longest_common_prefix(int i, int j, string& S, int N) {
    int l = 0, h = N-1;
    while (l <= h) {
        int m = (h-l)/2 + l;

        int init_i = i, end_i = i + m;
        int init_j = j, end_j = j + m;

        

        if (equal_substrings(init_i+1, end_i+1, init_j+1, end_j+1, N))
            l = m+1;
        else h = m-1;
    }

    return h;
}

void solve(string& S) {
    int N = S.length();

    compute_prefix_hash(S, N);

    vector<int> indices = least_char_indices(S, N);
    int M = indices.size();
    int min_rota_idx = indices[0];
    for (int i = 1; i < M; i++) {
        int m = longest_common_prefix(min_rota_idx, indices[i], S, N);

        char first_next_char = S[(min_rota_idx + m + 1) % N];
        char second_next_char = S[(indices[i] + m + 1) % N];
        if (first_next_char > second_next_char)
            min_rota_idx = indices[i];
    }

    print_rotation(S, N, min_rota_idx);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);
    
    return 0;
}