// Subarray Distinct Values (CSES)
 
#include <iostream>
#include <vector>
#include <unordered_map>
 
using namespace std;
using ll = long long;
 
// Time: O(N)
// Space: O(K)
 
void solve(vector<int>& A, int N, int K) {
    unordered_map<int,int> uMap;
    int j = 0; ll count = 0;
    for (int i = 0; i < N; i++) {
        uMap[A[i]]++;

        while (j <= i && uMap.size() > K) {
            if (uMap[A[j]] == 1)
                uMap.erase(A[j]);
            else uMap[A[j]]--;
            j++;
        }

        int w_size = i-j+1;
        count += w_size;
    }

    cout << count;
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