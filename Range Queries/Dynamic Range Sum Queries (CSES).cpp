// Dynamic Range Sum Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)
 
using ll_t = long long;

class SumSegmentTree {
public:
    SumSegmentTree(vector<ll_t>& arr) {
        int arr_sz = arr.size();
        tree_.assign(arr_sz * 4, 0);
        buildTree(0, arr_sz-1, 0, arr);
    }

    ll_t query(int low, int high, int node_idx, int query_low, int query_high) {
        if (query_low > query_high) {
            return 0;
        }
        if (low == query_low && high == query_high) {
            return tree_[node_idx];
        }

        int mid = (high - low) / 2 + low;
        ll_t left_sum = query(low, mid, 2*node_idx+1, query_low, min(mid, query_high));
        ll_t right_sum = query(mid+1, high, 2*node_idx+2, max(mid+1, query_low), query_high);

        return left_sum + right_sum;
    }

    void update(int low, int high, int node_idx, int update_idx, int update_val) {
        if (update_idx < low || update_idx > high) {
            return;
        }
        if (low == high && update_idx == low) {
            tree_[node_idx] = update_val;
            return;
        }

        int mid = (high - low) / 2 + low;
        update(low, mid, 2*node_idx+1, update_idx, update_val);
        update(mid+1, high, 2*node_idx+2, update_idx, update_val);
        
        tree_[node_idx] = tree_[2*node_idx+1] + tree_[2*node_idx+2]; 
    }

private:
    vector<ll_t> tree_;

    void buildTree(int low, int high, int node_idx, vector<ll_t>& arr) {
        if (low == high) {
            tree_[node_idx] = arr[low];
            return;
        }

        int mid = (high - low) / 2 + low;
        buildTree(low, mid, 2*node_idx+1, arr);
        buildTree(mid+1, high, 2*node_idx+2, arr);

        tree_[node_idx] = tree_[2*node_idx+1] + tree_[2*node_idx+2];
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_cnt, query_cnt;
    cin >> num_cnt >> query_cnt;

    vector<ll_t> nums(num_cnt);
    for (int i = 0; i < num_cnt; i++) {
        cin >> nums[i];
    }

    SumSegmentTree sum_seg_tree(nums);

    int query_type, update_idx, update_val;
    int range_low, range_high;
    for (int i = 0; i < query_cnt; i++) {
        cin >> query_type;
        if (query_type == 1) {
            cin >> update_idx >> update_val;
            sum_seg_tree.update(0, num_cnt-1, 0, update_idx-1, update_val);
        } else {
            cin >> range_low >> range_high;
            ll_t range_sum = sum_seg_tree.query(0, num_cnt-1, 0, range_low-1, range_high-1);
            cout << range_sum << endl;
        }
    }
    
    return 0;
}