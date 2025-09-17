// Elevator Rides (CSES)
 
#include <iostream>
#include <vector>
#include <bitset>
 
using namespace std;
 
// Time: O(2^N * N)
// Space: O(N)
 
using ll_t = long long;
using bitset_mask_t = bitset<MAX_PEOPLE_CNT>;

const int MAX_PEOPLE_CNT = 20;

// TODO
int countMinElevatorRides(
    int curr_people_idx,
    bitset_mask_t& mask,
    vector<vector<int>>& dp
) {
    return -1;
}

void solve(
    vector<int>& people_weights,
    int people_cnt,
    int max_elev_weight
) {
    bitset_mask_t mask;
    vector<vector<int>> dp(
        people_cnt+1, vector<int>((1 << 20), -1)        // 1 << 20 = 1e6
    );
    int min_elev_rides = countMinElevatorRides(
        0,
        mask,
        dp
    );

    cout << min_elev_rides << endl;
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