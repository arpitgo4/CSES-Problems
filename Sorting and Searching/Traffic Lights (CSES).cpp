// Traffic Lights (CSES)

#include <iostream>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

void solve(int N, vector<int>& A, int K) {
    multiset<int> d_oSet({ N });
    set<int> oSet;
    for (int i = 0; i < K; i++) {
        auto [ itr, _ ] = oSet.insert(A[i]);

        int l = itr == oSet.begin() ? 0 : *prev(itr);
        int h = itr == prev(oSet.end()) ? N : *next(itr);

        int og_dist = h-l;
        d_oSet.erase(d_oSet.find(og_dist));

        d_oSet.insert(A[i]-l);
        d_oSet.insert(h-A[i]);

        cout << (*d_oSet.rbegin()) << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<int> A(K);
    for (int i = 0; i < K; i++)
        cin >> A[i];

    solve(N, A, K);

    return 0;
}