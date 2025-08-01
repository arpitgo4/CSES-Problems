// Sliding Window Sum (CSES)
 
#include <iostream>
#include <vector>
#include <deque>
 
using namespace std;
 
// Time: O(N)
// Space: O(K)
 
using ll_t = long long;

ll_t generateNextElement(
    ll_t prev_element,
    ll_t coeff_a,
    ll_t const_b,
    ll_t mod_c
) {
    return ((coeff_a * prev_element) + const_b) % mod_c;
}

void solve(
    int elem_cnt,
    int wnd_sz,
    ll_t init_elem,
    ll_t coeff_a,
    ll_t const_b,
    ll_t mod_c
) {
    deque<ll_t> window;
    window.emplace_back(init_elem);
    ll_t wnd_sum = init_elem;
    for (int i = 1; i < wnd_sz; i++) {
        ll_t next_elem = generateNextElement(
            window.back(),
            coeff_a,
            const_b,
            mod_c
        );
        window.emplace_back(next_elem);
        wnd_sum += next_elem;
    }

    ll_t sum_xor = wnd_sum;
    for (int i = wnd_sz; i < elem_cnt; i++) {
        ll_t next_elem = generateNextElement(
            window.back(),
            coeff_a,
            const_b,
            mod_c
        );
        window.emplace_back(next_elem);
        wnd_sum += next_elem;

        wnd_sum -= window.front();
        window.pop_front();

        sum_xor ^= wnd_sum;
    }

    cout << sum_xor << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int elem_cnt, wnd_sz;
    cin >> elem_cnt >> wnd_sz;

    ll_t init_elem, coeff_a, const_b, mod_c;
    cin >> init_elem >> coeff_a >> const_b >> mod_c;

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