// Sliding Window Median (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
 
// Time: O(NlogN + N)
// Space: O(NlogN)
 
/**
 * Note: sparse table approach will not work!
 * We need global mid values for the window not (max, min) values for two halves
 * of the window
 * 
 * Think along heaps more....
*/

vector<vector<int>> min_sp_table, max_sp_table;

// [1...N] elements
// max-heap - min-heap  (both will hold half of the entire window)
// max from max-heap => N/2
// min from min-heap => N/2
// element evicted from min-heap (min element) will go into max-heap
// leftmost element from the window has to be removed from the max-heap ???
// above can be achieved with Indexed Priority Queue (IPQ)
// can we use something less implementation intensive ???

void build_sparse_table(vector<int>& A, int N) {
    int max_pow = ceil(log2(N));
    min_sp_table.assign(max_pow+1, vector<int>(N, INT_MAX));
    max_sp_table.assign(max_pow+1, vector<int>(N, INT_MIN));

    for (int i = 0; i < N; i++)
        min_sp_table[0][i] = max_sp_table[0][i] = A[i];

    for (int pow = 1; pow <= max_pow; pow++)
        for (int i = 0; i < N; i++) {
            int a = min_sp_table[pow-1][i];
            int b_idx = i + (1 << (pow-1));
            int b = INT_MAX;
            if (b_idx < N)
                b = min_sp_table[pow-1][b_idx];

            min_sp_table[pow][i] = min(a, b);

            a = max_sp_table[pow-1][i];
            b_idx = i + (1 << (pow-1));
            b = INT_MIN;
            if (b_idx < N)
                b = max_sp_table[pow-1][b_idx];

            max_sp_table[pow][i] = max(a, b);
        }
}

int query_min(int i, int j) {
    int w_size = j-i+1;
    int pow = log2(w_size);
    int a = min_sp_table[pow][i];
    int b = min_sp_table[pow][j-(1 << pow)+1];

    return min(a, b);
}

int query_max(int i, int j) {
    int w_size = j-i+1;
    int pow = log2(w_size);
    int a = max_sp_table[pow][i];
    int b = max_sp_table[pow][j-(1 << pow)+1];

    return max(a, b);
}

void solve(vector<int>& A, int N, int K) {
    build_sparse_table(A, N);

    for (int i = K-1, j = 0; i < N; i++, j++) {
        if (K % 2 == 0) {
            int m = (i-j)/2 + j;
            int a = query_max(j, m);
            int b = query_min(m+1, i);
            cout << min(a, b) << " ";
        } else {
            int m = (i-j)/2 + j;
            cout << query_max(i, m) << " ";
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N, K);
    
    return 0;
}