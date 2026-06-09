// Apartments (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
 
using namespace std;
 
// Time: O(NlogN + MlogM)
// Space: O(N)
 
/**
 * Greedy Approach,
 * Sorted desired array and available apartments (indirectly by multiset), 
 * so that users with smallest asks get the smallest apartments avaialble within K variation
 * 
 * Without sorting desired array, there can be cases where user with bigger ask got a smaller apartment (ask-k)
 * which could have been allocated to next customer with smaller ask than previous one but that apartment is no
 * longer available
*/
void solve(
    vector<int>& desired_apt_size,
    int applicant_cnt,
    vector<int>& apartment_size,
    int apartment_cnt,
    int max_diff
) {
    sort(desired_apt_size.begin(), desired_apt_size.end());

    multiset<int> apartment_set(
        apartment_size.begin(),
        apartment_size.end()
    );

    int alloc_cnt = 0;
    for (int i = 0; i < (int) desired_apt_size.size(); i++) {
        int desired_size = desired_apt_size[i];
        multiset<int>::iterator itr = apartment_set.lower_bound(
            desired_size - max_diff
        );

        if (itr != apartment_set.end() && *itr <= (desired_size + max_diff)) {
            apartment_set.erase(itr);
            alloc_cnt++;
        }
    }

    cout << alloc_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int applicant_cnt, apartment_cnt, max_diff;
    cin >> applicant_cnt >> apartment_cnt >> max_diff;
    
    vector<int> desired_apt_size(applicant_cnt);
    for (int i = 0; i < applicant_cnt; i++) {
        cin >> desired_apt_size[i];
    }

    vector<int> apartment_size(apartment_cnt);
    for (int i = 0; i < apartment_cnt; i++) {
        cin >> apartment_size[i];
    }

    solve(
        desired_apt_size,
        applicant_cnt,
        apartment_size,
        apartment_cnt,
        max_diff
    );
    
    return 0;
}