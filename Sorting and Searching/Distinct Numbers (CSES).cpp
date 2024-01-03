// Distinct Numbers (CSES)

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Time: O(NlogN)
// Space: O(1)
void solve2(vector<int>& A) {
    sort(A.begin(), A.end());

    int N = A.size(), counter = 1;
    for (int i = 1; i < N; i++)
        if (A[i-1] != A[i])
            counter++;

    cout << counter << endl;
}

// Time: O(N)
// Space: O(N)
void solve1(vector<int>& A) {
    unordered_set<int> uSet;
    for (int a : A)
        uSet.insert(a);

    cout << uSet.size() << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    // solve1(A);
    solve2(A);

    return 0;
}