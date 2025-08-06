// Sliding Window Mode (CSES)
 
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
 
using namespace std;
 
// Time: O(NlogK)
// Space: O(K)
 
void solve(
    vector<int>& elements,
    int elem_cnt,
    int wnd_sz
) {
    unordered_map<int,int> freq_map;

    auto cmp = [&](auto& a, auto& b) {
        if (freq_map[a] == freq_map[b]) {
            return a > b;
        }
        return freq_map[a] < freq_map[b];
    };
    set<int, decltype(cmp)> elem_set(cmp);

    for (int i = 0; i < wnd_sz; i++) {
        int element = elements[i];
        elem_set.erase(element);
        freq_map[element]++;
        elem_set.emplace(element);
    }

    cout << (*elem_set.rbegin()) << " ";
    for (int i = wnd_sz; i < elem_cnt; i++) {
        int elem_to_insert = elements[i];
        elem_set.erase(elem_to_insert);
        freq_map[elem_to_insert]++;
        elem_set.emplace(elem_to_insert);

        int elem_to_remove = elements[i-wnd_sz];
        elem_set.erase(elem_to_remove);
        freq_map[elem_to_remove]--;
        if (freq_map[elem_to_remove] > 0) {
            elem_set.emplace(elem_to_remove);
        }

        cout << (*elem_set.rbegin()) << " ";
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