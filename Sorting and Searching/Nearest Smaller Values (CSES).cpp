// Nearest Smaller Values (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
/**
 * Can also be done with Monotonic stack!, O(3N) ~ O(N)
 * Can also use Segment trees for stable O(logN) searching, Time: O(N + NlogN)
*/

// Time: N * [O(1), O(logN), O(N)] ~ [O(N), O(NlogN), O(N^2)]
// Space: O(N)
 
vector<int> P;

void solve(vector<int>& A, int N) {
    P.assign(N+1, 0);

    for (int i = 1; i < N+1; i++) {
        int j = i-1;
        while (A[j] >= A[i])
            j = P[j];
        P[i] = j;

        cout << P[i] << " "; 
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<int> A(N+1, 0);
    for (int i = 1; i < N+1; i++)
        cin >> A[i];

    solve(A, N);
    
    return 0;
}