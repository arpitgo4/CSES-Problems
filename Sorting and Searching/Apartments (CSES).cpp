// Apartments (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Time: O(NlogN + MlogM)
// Space: O(N)

/**
 * Greedy approach, 
 * Allocate smallest desired apartment to each customer so that customers after that which will have bigger asks
 * can be allocated rest of the bigger ones.
 * 
 * For above approach, asks have be sorted in non-decreasing order.
 * 
 * Sorted desired array and available apartments (indirectly by multiset), 
 * so that users with smallest asks get the smallest apartments avaialble within K variation
 * 
 * Without sorting desired array, there can be cases where user with bigger ask got a smaller apartment (ask-k)
 * which could have been allocated to next customer with smaller ask than previous one but that apartment is no
 * longer available
*/

void solve(vector<int>& apartments, vector<int>& desired, int N, int M, int K) {
    sort(desired.begin(), desired.end());

    multiset<int> oms(apartments.begin(), apartments.end());

    int counter = 0;
    for (int d : desired) {
        auto itr = oms.lower_bound(d-K);
        if (itr != oms.end()) {
            if (*itr <= d+K) {
                counter++;
                oms.erase(itr);
            }
        }
    }

    cout << counter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> desired(N);
    for (int i = 0; i < N; i++)
        cin >> desired[i];

    vector<int> apartments(M);
    for (int i = 0; i < M; i++)
        cin >> apartments[i];

    solve(apartments, desired, N, M, K);

    return 0;
} 