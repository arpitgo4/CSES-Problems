// Tasks and Deadlines (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
// Time: O(NlogN)
// Space: O(N)

using ll_t = long long;

class Task {
public:
    int duration_;
    int deadline_;
    int idx_;

    Task(int duration, int deadline, int idx) {
        duration_ = duration;
        deadline_ = deadline;
        idx_ = idx;
    }
};

/**
 * Duration and Deadline both factors influence
 * the reward for each task.
 * 
 * Reward[i] = deadline[i] - curr_time
 * 
 * 1. Prioritize task that has earlier deadline
 * 2. Prioritize task that has longer duration
 * 
 * Deadline and duration for any task are constant.
 * Reward for each tasks depends on the current time.
 * 
 * We need efficient look-up for a task from remaining 
 * tasks that will give me maximum reward based on the
 * current time.
 * 
 * Reward[i] = (deadline[i] - (curr_time + duration[i]))
 * Reward[i] = (deadline[i] - curr_time - duration[i])
 * 
 * or,
 * finish_time = curr_time + duration[i]
 * Reward[i] = (deadline[i] - finish_time)
 * 
 * In order to maximuze reward[i] in above equation, we have to
 * minimize curr_time for each task.
 * In other words, we can minimize start_time, or, start each task
 * as soon as possible.
 * 
 * Otherway to think is, minimize chance of any task giving negative
 * reward.
 * 
 * Setting all the above reasoning aside,
 * 
 * Tried running different approaches on the given sample data and 
 * found the maximum for it,
 * 1. Ascending sort by deadline
 * 2. Descending sort by deadline
 * 3. Ascending sort by duration (this gave maxima for the given example)
 * 4. Descending sort by duration
 * 
 * Approach #3 also worked for all the test cases. Hence, this greedy
 * strategy gives the maxima for this function.
 */
void solve(vector<Task>& tasks, int task_cnt) {
    auto cmp = [&](const auto& t1, const auto& t2) {
        if (t1.duration_ == t2.duration_) {
            return t1.deadline_ < t2.deadline_;
        }
        return t1.duration_ < t2.duration_;
    };
    sort(tasks.begin(), tasks.end(), cmp);

    ll_t total_reward = 0;
    ll_t curr_time = 0;
    ll_t finish_time = 0;
    for (int i = 0; i < task_cnt; i++) {
        finish_time = curr_time + tasks[i].duration_; 
        total_reward += (tasks[i].deadline_ - finish_time);

        curr_time = finish_time;
    }

    cout << total_reward << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int task_cnt;
    cin >> task_cnt;
    
    int duration, deadline;
    vector<Task> tasks;
    for (int i = 0; i < task_cnt; i++) {
        cin >> duration >> deadline;
        tasks.emplace_back(duration, deadline, i);
    }

    solve(tasks, task_cnt);
    
    return 0;
}