// Finding Periods (CSES)

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

/**
 * Implementation with Rolling Hash gives,
 * Time: O(N * (sum of harmonic series)) ~ O(N * ln(N))
 * 
 * sum of harmonic series can be represented as Natural Logarithm (log with base `e`)
*/

// Time: O(NlnN)              // natural logarithm
// Space: O(N)

const ll P = 31;
const ll M = 1e9 + 7;

vector<ll> hash_prefix;
vector<ll> powers;

void compute_hash_prefix(string& S, int N) {
    hash_prefix.assign(N+1, 0);
    powers.assign(N+1, 1);

    for (int i = 1; i < N+1; i++) {
        powers[i] = (powers[i-1] * P) % M;
        int c_val = S[i-1] - 'a';
        hash_prefix[i] = (hash_prefix[i-1] + (c_val * powers[i]) % M) % M;
    }
}

bool compare_substrings(int i, int j, int p, int q, int N) {
    // handles the case for partial prefixes
    if (q > N) {                            // q >= N+1
        int diff = q - N;
        q = N;
        j -= diff;
    }

    ll h1 = (hash_prefix[j] - hash_prefix[i-1] + M) % M;
    ll h2 = (hash_prefix[q] - hash_prefix[p-1] + M) % M;

    ll normalized_h1 = (h1 * powers[q-j]) % M;

    return normalized_h1 == h2;
}

void solve(string& S) {
    int N = S.length();

    compute_hash_prefix(S, N);

    for (int i = 0; i < N; i++) {

        int prefix_length = i+1;        // i-0+1;   // j = 0, for prefix window
        int k = 0;
        while (k < N) {
            
            // hash(0, i) == hash(k, k+prefix_length-1)
            // hash(0, 0) == hash(0, 0)         // first edge case
            // hash(0, N-1) == hash(0, N-1)     // end edge case
            // 1 based => hash(1, i+1) == hash(k+1, k+prefix_length)
            if (!compare_substrings(1, i+1, k+1, k+prefix_length, N))
                break;
            
            k += prefix_length;
        }

        if (k >= N)
            cout << (i+1) << " ";       // period found
    }
}

// Time: O(N^2)
// Space: O(1)
bool isPrefix(string& S, string& prefix) {
    int i = 0, j = 0;
    int N = S.length(), M = prefix.length();
    while (i < N) {
        while (i < N && j < M && S[i] == prefix[j]) {
            i++;
            j++;
        }

        if (i == N)
            break;
        if (j != M)
            return false;

        j = 0;
    }

    return true;
}

void solve_brute(string& S) {
    int N = S.length();

    vector<int> periods;
    string prefix = "";
    for (int i = 0; i < N; i++) {
        prefix += S[i];
        if (isPrefix(S, prefix))
            periods.push_back(i+1);
    }

    for (int p : periods)
        cout << p << " ";
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