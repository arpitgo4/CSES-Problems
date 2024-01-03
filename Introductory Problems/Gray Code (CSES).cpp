// Gray Code (CSES)

#include <iostream>
#include <algorithm>

using namespace std;

// Time: O(2^N)
// Space: O(1)

// Time: O(N)
// Space: O(N)
void to_binary(int num, int N) {
    int counter = 0;
    vector<int> res(N);
    int idx = N-1;
    while (idx >= 0) {
        res[idx] = (num & 1);
        num = num >> 1;
        idx--;
    }

    for (int a : res)
        cout << a;
    cout << endl;
}

void solve(int N) {
    int prev = 0;
    to_binary(prev, N);
    for (int i = 1; i <= (1 << N); i++) {
        int bit_diff = __builtin_popcount(i ^ prev);
        if (bit_diff == 1) {
            to_binary(i, N);
            prev = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    solve(N);

    return 0;
}