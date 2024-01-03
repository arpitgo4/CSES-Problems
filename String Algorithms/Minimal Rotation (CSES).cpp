// Minimal Rotation (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;
using ll = long long;

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

const ll P = 31;
const ll M = 1e9 + 7;

void solve(string& S) {
    int N = S.length();

    int min_start_idx = -1;
    ll min_hash = LLONG_MAX;
    ll hash = 0ll;
    for (int i = 0; i < N; i++) {
        hash = 0ll;
        int count = 0;
        int j = i % N;
        while (count < N) {
            ll power = pow(P, N-count-1);
            ll c_val = S[j] - 'a';
            hash = (hash + c_val * power) % M;
            j = (j + 1) % N;
            count++;
        }

        if (hash < min_hash) {
            min_hash = hash;
            min_start_idx = i;
        }
    }

    string minimal_rotation = "";
    int count = 0;
    int j = min_start_idx % N;
    while (count < N) {
        minimal_rotation += S[j];
        j = (j + 1) % N;
        count++;
    }

    cout << minimal_rotation;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    cin >> S;

    solve(S);
    
    return 0;
}