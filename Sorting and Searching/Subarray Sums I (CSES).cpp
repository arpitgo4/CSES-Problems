// Subarray Sums I (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;
 
// Time: O(N)
// Space: O(1)

void solve(vector<int>& A, int N, int K) {
    ll sum = 0, counter = 0;
    int j = 0;
    for (int i = 0; i < N; i++) {
        sum += A[i];
        while (j <= i && sum > K) {
            sum -= A[j];
            j++;
        }

        if (sum == K)
            counter++;
    }

    cout << counter;
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