// Nested Ranges Check (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <tuple>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)

/**
 * For this problem, both subproblems needs to
 * two inequality relations.
 * 
 * General idea to implement 2 inequalities look-up
 * efficiently here is to have 2 sorted orders present.
 * With sorted orders we can perform both inequality checks
 * in O(logN) time.
 */
 
using range_t = tuple<int,int,int>;

const int INF = INT_MAX;

/**
 * For a given range to contain another range,
 * other ranges',
 * 
 * given_x1 <= other_x1 && given_x2 >= other_x2
 * 
 * Sort given data based on the starting ends of all
 * ranges.
 */
void itContainsSomeOtherRange(
    vector<range_t>& ranges,
    int range_cnt,
    vector<bool>& any_contained
) {

    auto cmp = [&](const auto& r1, const auto& r2) {
        if (get<0>(r1) == get<0>(r2)) {
            return get<1>(r1) > get<1>(r2);
        }
        return get<0>(r1) < get<0>(r2);
    };
    sort(ranges.begin(), ranges.end(), cmp);

    auto set_cmp = [&](const auto& r1, const auto& r2) {
        return get<1>(r1) < get<1>(r2);
    };
    multiset<range_t, decltype(set_cmp)> range_set(set_cmp);

    for (int i = range_cnt-2; i >= 0; i--) {
        range_set.insert(ranges[i+1]);
        int x1 = get<0>(ranges[i]);
        int x2 = get<1>(ranges[i]);
        auto itr = range_set.lower_bound({ INF, x1, INF });
        if (itr != range_set.end() && get<1>(*itr) <= x2) {
            int idx = get<2>(ranges[i]);
            any_contained[idx] = true;
        }
    }
}

/**
 * Sort given data based on the starting ends of all 
 * ranges.
 * 
 * Use a running sorted data structure to arrange all
 * the seen ranges so far. This sorted data structure
 * can be used to quickly look-up by ending point, if 
 * any range contains the current range.
 */
void someOtherRangeContainsIt(
    vector<range_t>& ranges,
    int range_cnt,
    vector<bool>& any_contains
) {

    auto cmp = [&](const auto& r1, const auto& r2) {
        if (get<0>(r1) == get<0>(r2)) {
            return get<1>(r1) > get<1>(r2);
        }
        return get<0>(r1) < get<0>(r2);
    };
    sort(ranges.begin(), ranges.end(), cmp);

    auto set_cmp = [&](const auto& r1, const auto& r2) {
        return get<1>(r1) < get<1>(r2);
    };
    multiset<range_t, decltype(set_cmp)> range_set(set_cmp);

    for (int i = 1; i < range_cnt; i++) {
        range_set.insert(ranges[i-1]);
        int x2 = get<1>(ranges[i]);
        auto itr = range_set.lower_bound({ INF, x2, INF });
        if (itr != range_set.end()) {
            int idx = get<2>(ranges[i]);
            any_contains[idx] = true;
        }
    }
}

void solve(vector<range_t>& ranges, int range_cnt) {
    vector<bool> any_contained(range_cnt, false);
    itContainsSomeOtherRange(ranges, range_cnt, any_contained);

    vector<bool> any_contains(range_cnt, false);
    someOtherRangeContainsIt(ranges, range_cnt, any_contains);

    for (bool contained : any_contained) {
        cout << (contained ? 1 : 0) << " ";
    }
    cout << endl;

    for (bool contain : any_contains) {
        cout << (contain ? 1 : 0) << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int range_cnt;
    cin >> range_cnt;
    
    int x1, x2;
    vector<range_t> ranges(range_cnt);
    for (int i = 0; i < range_cnt; i++) {
        cin >> x1 >> x2;
        ranges[i] = { x1, x2, i };
    }

    solve(ranges, range_cnt);
    
    return 0;
}