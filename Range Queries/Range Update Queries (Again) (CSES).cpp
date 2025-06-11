// Range Update Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)
 
using ll_t = long long;

class SegmentTree {
public:
    SegmentTree(vector<ll_t>& arr) {
        int arr_sz = arr.size();
        tree_.assign(arr_sz * 4, 0);
        lazy_.assign(arr_sz * 4, 0);
        buildTree(0, arr_sz-1, 0, arr);
    }

    ll_t queryPoint(int low, int high, int node_idx, int query_idx) {
        if (query_idx < low || query_idx > high) {
            return 0;
        }
        if (low == high && query_idx == low) {
            return tree_[node_idx];
        }

        pushLazyUpdate(low, high, node_idx);

        int mid = (high - low) / 2 + low;
        if (query_idx <= mid) {
            return queryPoint(low, mid, 2*node_idx+1, query_idx);
        } else {
            return queryPoint(mid+1, high, 2*node_idx+2, query_idx);
        }
    }

    void updateRange(int low, int high, int node_idx, int update_low, int update_high, int update_val) {
        if (update_low > update_high) {
            return;
        }
        if (low == update_low && high == update_high) {
            int seg_sz = high - low + 1;
            tree_[node_idx] += (seg_sz * update_val);
            lazy_[node_idx] += update_val;
            return;
        }

        pushLazyUpdate(low, high, node_idx);

        int mid = (high - low) / 2 + low;
        updateRange(low, mid, 2*node_idx+1, update_low, min(mid, update_high), update_val);
        updateRange(mid+1, high, 2*node_idx+2, max(mid+1, update_low), update_high, update_val);

        tree_[node_idx] = tree_[2*node_idx+1] + tree_[2*node_idx+2];
    }

private:
    vector<ll_t> tree_;
    vector<ll_t> lazy_;

    void pushLazyUpdate(int low, int high, int node_idx) {
        int left_idx = 2 * node_idx + 1;
        int right_idx = left_idx + 1;

        int mid = (high - low) / 2 + low;
        tree_[left_idx] += (mid - low + 1) * lazy_[node_idx];
        tree_[right_idx] += (high - mid) * lazy_[node_idx];
        
        lazy_[left_idx] += lazy_[node_idx];
        lazy_[right_idx] += lazy_[node_idx];
        lazy_[node_idx] = 0;
    }

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

    SegmentTree seg_tree(nums);

    int query_type, update_low, update_high, query_idx;
    ll_t update_val;
    for (int i = 0; i < query_cnt; i++) {
        cin >> query_type;
        if (query_type == 1) {
            cin >> update_low >> update_high >> update_val;
            seg_tree.updateRange(0, num_cnt-1, 0, update_low-1, update_high-1, update_val);
        } else {
            cin >> query_idx;
            ll_t val = seg_tree.queryPoint(0, num_cnt-1, 0, query_idx-1);
            cout << val << endl;
        }
    }
    
    return 0;
}