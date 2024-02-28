// Sliding Window Cost (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O()
// Space: O()
 
void solve(vector<int>& A, int N, int K) {
    
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