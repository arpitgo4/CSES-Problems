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
    unordered_map<int, set<int>> freq_bucket;
    int max_freq = 0;
    for (int i = 0; i < wnd_sz; i++) {
        int elem = elements[i];
        int old_freq = freq_map[elem];
        freq_map[elem]++;
        int new_freq = freq_map[elem];

        if (old_freq > 0) {
            freq_bucket[old_freq].erase(elem);
        }

        freq_bucket[new_freq].emplace(elem);
        max_freq = max(max_freq, new_freq);
    }

    cout << (*freq_bucket[max_freq].begin()) << " ";
    for (int i = wnd_sz; i < elem_cnt; i++) {
        int elem_insert = elements[i];
        int old_freq = freq_map[elem_insert];
        freq_map[elem_insert]++;
        int new_freq = freq_map[elem_insert];

        if (old_freq > 0) {
            freq_bucket[old_freq].erase(elem_insert);
        }
        freq_bucket[new_freq].emplace(elem_insert);
        max_freq = max(max_freq, new_freq);

        int elem_remove = elements[i-wnd_sz];
        freq_bucket[freq_map[elem_remove]].erase(elem_remove);
        freq_map[elem_remove]--;
        if (freq_map[elem_remove] > 0) {
            freq_bucket[freq_map[elem_remove]].emplace(elem_remove);
        }

        // removed element moved to the one-step lower bucket
        if (freq_bucket[max_freq].empty())
            max_freq--;

        cout << (*freq_bucket[max_freq].begin()) << " ";
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