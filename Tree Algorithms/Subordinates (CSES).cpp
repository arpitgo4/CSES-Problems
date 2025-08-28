// Subordinates (CSES)
 
#include <iostream>
#include <vector>
#include <numeric>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
using tree_t = vector<vector<int>>;

void countSubordinates(
    int curr_employee,
    int prev_employee,
    tree_t& company_struct,
    int employee_cnt,
    vector<int>& subordinate_cnt
) {
    for (int next_employee : company_struct[curr_employee]) {
        if (next_employee != prev_employee) {
            countSubordinates(
                next_employee,
                curr_employee,
                company_struct,
                employee_cnt,
                subordinate_cnt
            );

            subordinate_cnt[curr_employee] += subordinate_cnt[next_employee] + 1;
        }
    }
}

void solve(
    int employee_cnt,
    vector<int>& boss
) {
    tree_t company_struct(employee_cnt+1, vector<int>());
    for (int i = 1; i <= employee_cnt; i++) {
        if (boss[i] != i) {
            company_struct[i].push_back(boss[i]);
            company_struct[boss[i]].push_back(i);
        }
    }

    vector<int> subordinate_cnt(employee_cnt+1, 0);
    countSubordinates(
        1,
        1,
        company_struct,
        employee_cnt,
        subordinate_cnt
    );

    for (int i = 1; i <= employee_cnt; i++) {
        cout << subordinate_cnt[i] << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int employee_cnt;
    cin >> employee_cnt;

    vector<int> boss(employee_cnt+1);
    iota(boss.begin(), boss.end(), 0);
    for (int i = 2; i <= employee_cnt; i++) {
        cin >> boss[i];
    }

    solve(employee_cnt, boss);
    
    return 0;
}