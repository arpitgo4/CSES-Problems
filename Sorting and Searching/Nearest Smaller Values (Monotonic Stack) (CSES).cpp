// Nearest Smaller Values (Monotonic Stack) (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)

void solve(vector<int>& nums, int num_cnt) {
    stack<pair<int,int>> num_stack;                         // monotonically-decreasing stack
    for (int i = 0; i < num_cnt; i++) {
        while (!num_stack.empty() && num_stack.top().first >= nums[i]) {
            num_stack.pop();
        }
        
        if (num_stack.empty()) {
            cout << 0 << " ";
        } else {
            cout << num_stack.top().second << " ";
        }

        num_stack.push({ nums[i], i+1 });
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_cnt;
    cin >> num_cnt;
    
    vector<int> nums(num_cnt);
    for (int i = 0; i < num_cnt; i++) {
        cin >> nums[i];
    }

    solve(nums, num_cnt);
    
    return 0;
}