// Sliding Window Xor (CSES)
 
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
    return ((coeff_a * prev_elem) + const_b) % mod_c;
}

void solve(
    int elem_cnt,
    int wnd_sz,
    int init_elem,
    int coeff_a,
    int const_b,
    int mod_c
) {
    deque<int> window{ init_elem };
    int wnd_xor = init_elem;
    for (int i = 0; i < wnd_sz-1; i++) {
        int next_elem = generateNextElement(
            window.back(),
            coeff_a,
            const_b,
            mod_c
        );
        window.emplace_back(next_elem);
        wnd_xor ^= next_elem;
    }

    int final_xor = wnd_xor;
    for (int i = wnd_sz; i < elem_cnt; i++) {
        int next_elem = generateNextElement(
            window.back(),
            coeff_a,
            const_b,
            mod_c
        );
        window.emplace_back(next_elem);
        wnd_xor ^= next_elem;

        wnd_xor ^= window.front();
        window.pop_front();

        final_xor ^= wnd_xor;
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