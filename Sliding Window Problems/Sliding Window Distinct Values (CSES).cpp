// Sliding Window Distinct Values (CSES)
 
#include <iostream>
#include <vector>
#include <unordered_map>
 
using namespace std;
 
// Time: O(N)
// Space: O(K)
 
void solve(
    vector<int>& elements,
    int elem_cnt,
    int wnd_sz
) {
    unordered_map<int,int> window;
    for (int i = 0; i < wnd_sz; i++) {
        window[elements[i]]++;
    }
    
    cout << window.size() << " ";
    for (int i = wnd_sz; i < elem_cnt; i++) {
        int elem_to_erase = elements[i-wnd_sz];
        window[elem_to_erase]--;
        if (window[elem_to_erase] == 0) {
            window.erase(elem_to_erase);
        }

        window[elements[i]]++;

        cout << window.size() << " ";
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