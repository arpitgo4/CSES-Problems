// Sliding Window Minimum (CSES)
 
#include <iostream>
#include <vector>
#include <deque>
 
using namespace std;
 
// Time: O(N)
// Space: O(K)
 
using ll_t = long long;

int generateNextElement(
    ll_t prev_elem,
    ll_t coeff_a,
    ll_t const_b,
    ll_t mod_c
) {
    return ((prev_elem * coeff_a) + const_b) % mod_c;
}

void solve(
    int elem_cnt,
    int wnd_sz,
    int init_elem,
    int coeff_a,
    int const_b,
    int mod_c
) {
    deque<int> window { init_elem };
    deque<int> mono_window { init_elem };                                     // monotonically decreasing deque
    for (int i = 0; i < wnd_sz-1; i++) {
        int next_elem = generateNextElement(
            window.back(),
            coeff_a,
            const_b,
            mod_c
        );

        while (!mono_window.empty() && mono_window.back() > next_elem) {
            mono_window.pop_back();
        }
        mono_window.emplace_back(next_elem);
        window.emplace_back(next_elem);
    }

    int final_xor = mono_window.front();
    for (int i = wnd_sz; i < elem_cnt; i++) {
        int next_elem = generateNextElement(
            window.back(),
            coeff_a,
            const_b,
            mod_c
        );

        while (!mono_window.empty() && mono_window.back() > next_elem) {
            mono_window.pop_back();
        }
        mono_window.emplace_back(next_elem);
        window.emplace_back(next_elem);

        if (!mono_window.empty() && mono_window.front() == window.front()) {
            mono_window.pop_front();
        }
        window.pop_front();

        final_xor ^= mono_window.front();
    }

    cout << final_xor << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int elem_cnt, wnd_sz;
    cin >> elem_cnt >> wnd_sz;

    int init_elem, coeff_a, const_b, mod_c;
    cin >> init_elem
        >> coeff_a
        >> const_b
        >> mod_c;

    solve(
        elem_cnt,
        wnd_sz,
        init_elem,
        coeff_a,
        const_b,
        mod_c
    );
    
    return 0;
}