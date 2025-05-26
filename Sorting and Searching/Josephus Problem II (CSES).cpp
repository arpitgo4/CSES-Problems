// Josephus Problem II (CSES)
 
#include <iostream>
 
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
// Time: O(NlogN)
// Space: O(N)
 
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

/**
 * We need to simulate complete elimination process.
 * There is no shortcut way for that.
 * 
 * If in case we needed to know just the survivor
 * we could have used the recursive formula.
 * 
 * We can use OrderedSet or Segment Tree for 
 * efficient `skip_cnt` look-ups.
 */
void solve(int children_cnt, int skip_cnt) {
    ordered_set ord_set;
    for (int i = 1; i <= children_cnt; i++) {
        ord_set.insert(i);
    }

    int curr_idx = 0;
    auto curr_itr = ord_set.find_by_order(curr_idx);
    while (!ord_set.empty()) {
        curr_idx = (curr_idx + skip_cnt) % ord_set.size();
        curr_itr = ord_set.find_by_order(curr_idx);

        cout << (*curr_itr) << " ";
        curr_itr = ord_set.erase(curr_itr);
        curr_idx = ord_set.order_of_key(*curr_itr);
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int children_cnt, skip_cnt;
    cin >> children_cnt >> skip_cnt;

    solve(children_cnt, skip_cnt);
    
    return 0;
}