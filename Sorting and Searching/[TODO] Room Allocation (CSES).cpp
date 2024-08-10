// Room Allocation (CSES)
 
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <tuple>
#include <algorithm>
 
using namespace std;

// Time: O(NlogN)
// Space: O(N)


vector<pair<int,int>> new_arrivals, new_departures;

void sort_by_start_time(vector<int>& arrivals, vector<int>& departures, int N) {
    vector<tuple<int,int,int>> A(N);
    for (int i = 0; i < N; i++)
        A[i] = { arrivals[i], departures[i], i };

    sort(A.begin(), A.end(), [&](const auto& t1, const auto& t2){
        int a1 = get<0>(t1), a2 = get<0>(t2);
        int d1 = get<1>(t1), d2 = get<1>(t2);
        int id1 = get<2>(t1), id2 = get<2>(t2);

        if (a1 == a2) {
            if (d1 == d2)
                return id1 < id2;
            else return d1 < d2;
        }

        return a1 < a2;
    });

    new_arrivals.resize(N);
    new_departures.resize(N);

    int i = 0;
    int arr, dep, idx;
    for (auto& t : A) {
        tie(arr, dep, idx) = t;
        new_arrivals[i] = { arr, idx };
        new_departures[i] = { dep, idx };
        i++;
    }
}

void solve(vector<int>& arrivals, vector<int>& departures, int N) {
    auto comp = [&](const int a, const int b) {
        return a > b;
    };
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);              // min-heap
    for (int i = 1; i <= N; i++)
        pq.push(i);

    int num_rooms = 0;
    vector<int> alloted_rooms(N, -1);

    sort_by_start_time(arrivals, departures, N);

    new_arrivals.push_back({ INT_MAX, -1 });
    new_departures.push_back({ INT_MAX, -1 });
    int i = 0, j = 0;
    while (i < N || j < N) {
        int arrive_time = new_arrivals[i].first;
        int departure_time = new_departures[i].first;
        int arrive_idx = new_arrivals[i].second;
        int departure_idx = new_departures[i].second;

        if (arrive_time <= departure_time) {                      // guest arrived
            int room = pq.top();
            num_rooms = max(num_rooms, room);
            pq.pop();
            alloted_rooms[arrive_idx] = room;
            i++;
        } else if (arrive_time > departure_time) {               // guest departed
            pq.push(alloted_rooms[departure_idx]);
            j++;
        } else {                                // handle case where arrival and departure are same day
            int room = pq.top();
            alloted_rooms[arrive_idx] = room;
            num_rooms = max(num_rooms, room);
            pq.push(alloted_rooms[departure_idx]);
            i++;
            j++;
        }
    }

    cout << num_rooms << endl;
    for (int r : alloted_rooms)
        cout << r << " ";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<int> arrivals(N), departures(N);
    for (int i = 0; i < N; i++)
        cin >> arrivals[i] >> departures[i];

    solve(arrivals, departures, N);
    
    return 0;
}