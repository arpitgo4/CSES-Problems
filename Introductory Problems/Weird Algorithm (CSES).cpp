// Weird Algorithm (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N)
// Space: O(N)

void solve(long long N) {
    vector<long long> res{N};

    while (N != 1) {
        if (N & 1)
            N = N*3 + 1;
        else N = N >> 1;

        res.push_back(N);
    }

    for (long long a : res)
        cout << a << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    cin >> N;

    solve(N);

    return 0;
}