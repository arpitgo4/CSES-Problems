// Elevator Rides (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
 
using namespace std;
 
// Time: O(N!)
// Space: O(N)
 
using ll_t = long long;

const int INF = INT_MAX;

void solve(
    vector<int>& people_weights,
    int people_cnt,
    int max_elev_weight
) {
    
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int people_cnt, max_elev_weight;
    cin >> people_cnt 
        >> max_elev_weight;

    vector<int> people_weights(people_cnt);
    for (int i = 0; i < people_cnt; i++) {
        cin >> people_weights[i];
    }

    solve(
        people_weights,
        people_cnt,
        max_elev_weight
    );
    
    return 0;
}