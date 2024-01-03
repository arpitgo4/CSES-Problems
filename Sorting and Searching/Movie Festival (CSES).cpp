// Movie Festival (CSES)

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// Time: O(NlogN)
// Space: O(1)

/**
 * When we sorted intervals by end time we sorted out the ambiguity at one side of data.
 * Now, we only need to care about the start time.
 * Above procedure, simplified the number of possible cases at the expense of O(NlogN) pre-processing time
 * 
 * Also, finding duplicates or overlapping intervals is much easier when data is sorted i.e. possible
 * duplicated or overlapping intervals are adjancent. Simple linear scan will be able to catch them now.
 * 
 * Other way is to create a BST for duplicated values or Interval tree for interval data types to catch
 * possible overlaps and duplicates.
 * 
 * Above, dynamic data structures are only useful in case we need delete operations. For simple search 
 * use-case, one time cost of sorting yields much better time complexity.
*/

void solve(vector<pair<int,int>>& A, int N) {
    
    sort(A.begin(), A.end(), [&](auto& p1, auto& p2) {
        return p1.second < p2.second;
    });

    int counter = 1;
    pair<int,int> last_movie = A[0];
    for (int i = 1; i < N; i++) {
        pair<int,int>& curr = A[i];
        int end_time = last_movie.second;
        int start_time = curr.first;
    
        if (end_time <= start_time) {
            counter++;
            last_movie = curr;
        }
    }

    cout << counter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<pair<int,int>> A(N);
    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        A[i] = { a, b };
    }

    solve(A, N);

    return 0;    
}
