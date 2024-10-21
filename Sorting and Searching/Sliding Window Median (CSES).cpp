// Sliding Window Median (CSES)
 
#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
// Time: O(NlogN)
// Space: O(N)

/**
 * Odd number of elements have true median or middle element,
 * middle = N/2
 * 
 * Even number of elements doesn't have a median or middle element per say.
 * In a way it has two middle elements and we have to resort to either one 
 * of them. Usually, we tend towards the left one.
 * 
 * middle_1 = N/2 - 1
 * middle_2 = N/2
 * 
 * General equation for middle elements in both parities,
 * middle = (N-1) / 2
 */

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

void print_median(ordered_set& oSet, int K) {
    int median = (*oSet.find_by_order((K-1)/2)).first;

    cout << median << " ";
}

void solve(vector<int>& A, int N, int K) {
    ordered_set oSet;

    int idx = 0;
    for (int i = 0; i < K; i++)
        oSet.insert({ A[i], idx++ });                             // to simulate multiset behaviour

    print_median(oSet, K);

    for (int i = K; i < N; i++) {
	    oSet.insert({ A[i], idx++ });                             // to simulate multiset behaviour
        oSet.erase(oSet.lower_bound({ A[i-K], 0 }));
        print_median(oSet, K);
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N, K);
    
    return 0;
}
