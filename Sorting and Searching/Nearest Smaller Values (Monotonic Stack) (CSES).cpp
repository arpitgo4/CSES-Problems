// Nearest Smaller Values (Monotonic Stack) (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
typedef long long ll;
 
// Time: O(N)
// Space: O(N)
 
void solve(vector<int>& A, int N) {
    stack<pair<int,int>> st;                    // monotonic stack of { A[i], i }

    for (int i = 0; i < N; i++) {
        while (!st.empty() && st.top().first >= A[i])
            st.pop();

        if (st.empty())
            cout << 0 << " ";
        else cout << st.top().second << " ";
            
        st.push({ A[i], i+1 });
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N);
    
    return 0;
}