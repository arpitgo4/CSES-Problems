// Sliding Window Median (CSES)
 
#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
 
// Time: O(NlogK)
// Space: O(K)

using ordered_stats_tree = tree<
    pair<int,int>,
    null_type,
    less<>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

void solve(
    vector<int>& elements,
    int elem_cnt,
    int wnd_sz
) {
    ordered_stats_tree elem_set;
    for (int i = 0; i < wnd_sz; i++) {
        elem_set.insert({ elements[i], i });
    }

    cout << (*elem_set.find_by_order((wnd_sz-1) / 2)).first << " ";
    for (int i = wnd_sz; i < elem_cnt; i++) {
        elem_set.insert({ elements[i], i });
        elem_set.erase(elem_set.lower_bound({ elements[i-wnd_sz], 0 }));

        cout << (*elem_set.find_by_order((wnd_sz-1) / 2)).first << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int elem_cnt, wnd_sz;
    cin >> elem_cnt >> wnd_sz;

    vector<int> elements(elem_cnt);
    for (int i = 0; i < elem_cnt; i++) {
        cin >> elements[i];
    }

    solve(elements, elem_cnt, wnd_sz);
    
    return 0;
}