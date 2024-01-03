// Restaurant Customers (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

// Time: O(NlogN)
// Space: O(1)

void solve(vector<int>& enter_time, vector<int>& exit_time, int N) {
    // added padding at the end to avoid bounds checking in the while loop
    enter_time.push_back(INT_MAX);
    exit_time.push_back(INT_MAX);

    sort(enter_time.begin(), enter_time.end());
    sort(exit_time.begin(), exit_time.end());

    int max_count = 0;
    int counter = 0;
    int i = 0, j = 0;
    while (i < N || j < N) {
        int a = enter_time[i];
        int b = exit_time[j];

        if (a < b) {
            counter++;
            i++;
        } else if (b < a) {
            counter--;
            j++;
        } else {        // a == b, when two people enter and exit at the same time
            i++;
            j++;            
        }

        max_count = max(max_count, counter);
    }

    cout << max_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> enter_time(N), exit_time(N);
    for (int i = 0; i < N; i++)
        cin >> enter_time[i] >> exit_time[i];

    solve(enter_time, exit_time, N);

    return 0;
}