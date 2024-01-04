// Sum of Three Values (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
using ll = long long;
 
// Time: O(N^2)
// Space: O(N)

void solve(vector<ll>& A, ll N, ll K) {
    vector<pair<ll,ll>> PA(N);
    for (int i = 0; i < N; i++)
        PA[i] = { A[i], i+1 };

    auto comp = [&](const pair<ll,ll>& p1, const pair<ll,ll>& p2) {
        return p1.first < p2.first;
    };
    sort(PA.begin(), PA.end(), comp);

    for (int i = 0; i < N; i++) {
        auto& a = PA[i];
        int l = i+1, h = N-1;
        while (l < h) {
            auto& b = PA[l];
            auto& c = PA[h];
            ll sum = a.first + b.first + c.first;
            if (sum < K) l++;
            else if (sum > K) h--;
            else {                                 // sum == K
                cout << a.second << " " << b.second << " " << c.second;
                return;
            }
        } 
    }

    cout << "IMPOSSIBLE";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll N, K;
    cin >> N >> K;

    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N, K);
    
    return 0;
}