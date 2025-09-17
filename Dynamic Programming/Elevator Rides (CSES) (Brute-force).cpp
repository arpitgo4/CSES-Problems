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

int countElevatorRides(
    vector<int>& people_weights,
    int people_cnt,
    int max_elev_weight
) {
    int ride_cnt = 1;
    ll_t curr_ride_weight = 0;
    int i = 0;
    while (i < people_cnt) {
        if ((curr_ride_weight + people_weights[i]) <= max_elev_weight) {
            curr_ride_weight += people_weights[i];
        } else {
            curr_ride_weight = people_weights[i];
            ride_cnt++;
        }
        i++;
    }

    return ride_cnt;
}

void solve(
    vector<int>& people_weights,
    int people_cnt,
    int max_elev_weight
) {
    sort(people_weights.begin(), people_weights.end());

    int min_elev_rides = INF;
    do {
        int rides_cnt = countElevatorRides(
            people_weights,
            people_cnt,
            max_elev_weight
        );

        min_elev_rides = min(
            min_elev_rides,
            rides_cnt
        );
    } while(next_permutation(
        people_weights.begin(), people_weights.end()
    ));

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