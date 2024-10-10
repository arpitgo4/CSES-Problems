// Room Allocation (CSES)
 
#include <iostream>
#include <vector>
#include <set>
#include <tuple>
 
using namespace std;

// Time: O(NlogN)
// Space: O(N)

/**
 * Line-Sweep Algorithm
 * 
 * Lay down all the arrival and departure data points on the
 * coordinate line (x-axis)
 * 
 * data point = (day number, status of movement, id of the person)
 * 
 * Custom sorting comparator
 * 1. Sort by day number first,
 * 2. If days are same, sort by status. Arrival will go first then departure
 * 3. If multiple people have same day & status, sort by id i.e. first come first serve basis 
 */

void solve(vector<int>& A, vector<int>& D, int N) {
    auto cmp = [&](const auto& t1, const auto& t2) {
        if (get<0>(t1) == get<0>(t2)) {
            if (get<1>(t1) == get<1>(t2))
                return get<2>(t1) < get<2>(t2);

            return get<1>(t1) > get<1>(t2);
        }

        return get<0>(t1) < get<0>(t2);
    };
    set<tuple<int,int,int>, decltype(cmp)> oSet(cmp);
    for (int i = 0; i < N; i++) {
        oSet.insert({ A[i], 1, i });
        oSet.insert({ D[i], -1, i });
    }

    int day, status, id;
    int max_rooms = 0, counter = 0;
    vector<int> alloc_rooms(N, -1);
    set<int> av_rooms;
    for (auto& itr : oSet) {
        tie(day, status, id) = itr;
        counter = counter + status;

        if (status == 1) {
            if (av_rooms.empty())
                alloc_rooms[id] = counter;
            else {
                alloc_rooms[id] = *av_rooms.begin();
                av_rooms.erase(av_rooms.begin());
            }
        }
        else av_rooms.insert(alloc_rooms[id]);
        
        max_rooms = max(max_rooms, counter);
    }

    cout << max_rooms << endl;
    for (int r : alloc_rooms)
        cout << r << " ";
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<int> A(N), D(N);
    for (int i = 0; i < N; i++)
        cin >> A[i] >> D[i];

    solve(A, D, N);
    
    return 0;
}