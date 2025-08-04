// Sliding Window Or (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)

/**
 * Bitwise OR operator is irreversible i.e.
 * you can't remove one number from aggregate
 * bitwise OR for some numbers.
 * 
 * In these cases, we can use the technique,
 * ** Prefix-Suffix blocks of fixed sizes **
 * to get the result for the windows of fixed
 * size for all elements in array.
 * 
 * Above technique comes under Divide & Conquer
 * class of algorithms. We have divided up the 
 * problem into fixed size subproblems and merging
 * these sub-problems to get the final result.
 */

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
    vector<ll_t> elements(elem_cnt);
    elements[0] = init_elem;
    for (int i = 1; i < elem_cnt; i++) {
        int next_elem = generateNextElement(
            elements[i-1],
            coeff_a,
            const_b,
            mod_c
        );

        elements[i] = next_elem;
    }

    // prefix ORs of wnd_sz-sized blocks
    vector<ll_t> prefix_ors(elem_cnt);
    prefix_ors[0] = init_elem;
    for (int i = 1; i < elem_cnt; i++) {
        if (i % wnd_sz == 0) {
            prefix_ors[i] = elements[i];
        } else {
            prefix_ors[i] = prefix_ors[i-1] | elements[i];
        }
    }

    // suffix ORs of wnd_sz-sized blocks
    vector<ll_t> suffix_ors(elem_cnt);
    suffix_ors[elem_cnt-1] = elements[elem_cnt-1];
    for (int i = elem_cnt-2; i >= 0; i--) {
        if (i % wnd_sz == 0) {
            suffix_ors[i] = elements[i];
        } else {
            suffix_ors[i] = suffix_ors[i+1] | elements[i];
        }
    }

    ll_t final_xor = 0;
    for (int i = wnd_sz-1; i < elem_cnt; i++) {
        final_xor ^= (prefix_ors[i] | suffix_ors[i-wnd_sz+1]); 
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