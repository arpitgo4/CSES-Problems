// Josephus Problem I (CSES)

#include <iostream>
#include <vector>

using namespace std;

// Time: O(N)
// Space: O(1)

void solve(int N) {
    int jump = 1;
    int idx = 1;
    while (counter <= N) {
        if (idx > N)
            jump++;

        idx = (idx + jump) % (N+1); 
        cout << idx << " ";

        idx++;
        counter++;
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
