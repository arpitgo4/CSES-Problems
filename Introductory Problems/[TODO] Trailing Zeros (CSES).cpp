// Trailing Zeros (CSES)
 
#include <iostream>
 
using namespace std;
 
// Time: O(log5(N))
// Space: O(1)
 
void solve(int N) {
    int count = 0, last_dig = 1;
    for (int x = N; x > 0; x--) {
        last_dig = (last_dig * x) % 10;
        if (last_dig == 0)
            count++;
    }

    cout << count << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    solve(N);
    
    return 0;
}