// Dynamic Range Minimum Queries (CSES)
 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)
 
const int INF = INT_MAX;

class MinSegmentTree {
public:
    MinSegmentTree(vector<int>& arr) {
        int arr_sz = arr.size();
        tree_.assign(arr_sz * 4, INF);
        buildTree(0, arr_sz-1, 0, arr);
    }

    int queryMin(int low, int high, int node_idx, int query_low, int query_high) {
        if (query_low > query_high) {
            return INF;
        }
        if (low == query_low && high == query_high) {
            return tree_[node_idx];
        }

        int mid = (high - low) / 2 + low;
        int left_min = queryMin(low, mid, 2*node_idx+1, query_low, min(mid, query_high));
        int right_min = queryMin(mid+1, high, 2*node_idx+2, max(mid+1, query_low), query_high);

        return min(left_min, right_min);
    }

    void updatePoint(int low, int high, int node_idx, int update_idx, int update_val) {
        if (update_idx < low || update_idx > high) {
            return;
        }
        if (low == high) {
            tree_[node_idx] = update_val;
            return;
        }

        int mid = (high - low) / 2 + low;
        updatePoint(low, mid, 2*node_idx+1, update_idx, update_val);
        updatePoint(mid+1, high, 2*node_idx+2, update_idx, update_val);

        tree_[node_idx] = min(tree_[2*node_idx+1], tree_[2*node_idx+2]);
    }

private:
    vector<int> tree_;

    void buildTree(int low, int high, int node_idx, vector<int>& arr) {
        if (low == high) {
            tree_[node_idx] = arr[low];
            return;
        }

        int mid = (high - low) / 2 + low;
        buildTree(low, mid, 2*node_idx+1, arr);
        buildTree(mid+1, high, 2*node_idx+2, arr);

        tree_[node_idx] = min(tree_[2*node_idx+1], tree_[2*node_idx+2]);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_cnt, query_cnt;
    cin >> num_cnt >> query_cnt;

    vector<int> nums(num_cnt);
    for (int i = 0; i < num_cnt; i++) {
        cin >> nums[i];
    }

    MinSegmentTree min_seg_tree(nums);

    int query_type, range_low, range_high, update_idx, update_val;
    for (int i = 0; i < query_cnt; i++) {
        cin >> query_type;
        if (query_type == 1) {
            cin >> update_idx >> update_val;
            min_seg_tree.updatePoint(0, num_cnt-1, 0, update_idx-1, update_val);
        } else {
            cin >> range_low >> range_high;
            int min_val = min_seg_tree.queryMin(0, num_cnt-1, 0, range_low-1, range_high-1);
            cout << min_val << endl;
        }
    }
    
    return 0;
}