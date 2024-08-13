// Number Spiral (CSES)

#include <iostream>
#include <vector>

using namespace std;

void solve(int row, int col) {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    int row, col;
    while (T-- > 0) {
        cin >> row >> col;
        solve(row-1, col-1);
    }

    return 0;
}