// Range Updates and Sums (CSES)
 
#include <iostream>
#include <vector>
#include <deque>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)

using ll_t = long long;

/**
 * Ordering both update operations efficiently is the
 * major challenge here.
 * 
 * Edge cases around merging both update operations
 * lazily.
 * 
 * Deque can be used to contain and order the update
 * operations.
 * Optimizations to keep the size of deque constant, so
 * that it can be pushed down to children nodes during
 * lazy push,
 * 1. Merge same subsequent operations into one entry in
 *    deque.
 * 2. Any new update operation will override all incremenet
 *    operations in deque.
 * 
 * With both above optimizations, at any time deque will only
 * have atmost 2 update operations.
 */
class SegmentTree {
public:
    SegmentTree(vector<ll_t>& arr) {
        int arr_sz = arr.size();
        tree_.assign(arr_sz * 4, 0);
        deque_.assign(arr_sz * 4, deque<pair<int,int>>());
        buildTree(0, arr_sz-1, 0, arr);
    }

    ll_t querySum(int low, int high, int node_idx, int range_low, int range_high) {
        if (range_low > range_high) {
            return 0;
        }
        if (low == range_low && high == range_high) {
            return tree_[node_idx];
        }

        pushLazyUpdate(low, high, node_idx);

        int mid = (high - low) / 2 + low;
        ll_t left_sum = querySum(low, mid, 2*node_idx+1, range_low, min(mid, range_high));
        ll_t right_sum = querySum(mid+1, high, 2*node_idx+2, max(mid+1, range_low), range_high);

        return left_sum + right_sum;
    }

    void updateRange(int low, int high, int node_idx, int range_low, int range_high, ll_t update_val) {
        if (range_low > range_high) {
            return;
        }
        if (low == range_low && high == range_high) {
            int seg_sz = high - low + 1;
            tree_[node_idx] = seg_sz * update_val;
            enqueueUpdate(low, high, node_idx, UPDATE_OPR, update_val);
            return;
        }

        pushLazyUpdate(low, high, node_idx);

        int mid = (high - low) / 2 + low;
        updateRange(low, mid, 2*node_idx+1, range_low, min(mid, range_high), update_val);
        updateRange(mid+1, high, 2*node_idx+2, max(mid+1, range_low), range_high, update_val);

        tree_[node_idx] = tree_[2*node_idx+1] + tree_[2*node_idx+2];
    }

    void incrementRange(int low, int high, int node_idx, int range_low, int range_high) {
        if (range_low > range_high) {
            return;
        }
        if (low == range_low && high == range_high) {
            int seg_sz = high - low + 1;
            tree_[node_idx] += seg_sz;
            enqueueUpdate(low, high, node_idx, INCR_OPR);
            return;
        }

        pushLazyUpdate(low, high, node_idx);

        int mid = (high - low) / 2 + low;
        incrementRange(low, mid, 2*node_idx+1, range_low, min(mid, range_high));
        incrementRange(mid+1, high, 2*node_idx+2, max(mid+1, range_low), range_high);

        tree_[node_idx] = tree_[2*node_idx+1] + tree_[2*node_idx+2];
    }

private:
    const int INCR_OPR = 1;
    const int UPDATE_OPR = 2;

    vector<ll_t> tree_;
    vector<deque<tie<int,int,int,ll_t>>> deque_;

    void enqueueUpdate(int low, int high, int node_idx, int update_op, ll_t update_val) {
        if (update_op == INCR_OPR) {
            if (!deque_[node_idx].empty()) {
                int op_type = deque_[node_idx].front();
            } else {
                deque_[node_idx].push_front({ low, high, update_op, -1 });
            }
        } else {
            while (!deque_[node_idx].empty()) {
                deque_[node_idx].pop_front();
            }

            deque_[node_idx].push_front({ low, high, update_op, update_val });
        }
    }

    void pushLazyUpdate(int low, int high, int node_idx) {

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

    int query_type, range_low, range_high;
    ll_t increment_val, update_val;
    for (int i = 0; i < query_cnt; i++) {
        cin >> query_type >> range_low >> range_high;
        if (query_type == 1) {
            cin >> increment_val;
            seg_tree.incrementRange(0, num_cnt-1, 0, range_low-1, range_high-1);
        } else if (query_type == 2) {
            cin >> update_val;
            seg_tree.updateRange(0, num_cnt-1, 0, range_low-1, range_high-1, update_val);
        } else {
            ll_t sum = seg_tree.querySum(0, num_cnt-1, 0, range_low-1, range_high-1);
            cout << sum << endl;
        }
    }
    
    return 0;
}