// Building Teams (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(V + E)
// Space: O(V + E)
 
class Friendship {
public:
    int pupil_a_;
    int pupil_b_;
    Friendship(int pupil_a, int pupil_b) {
        pupil_a_ = pupil_a;
        pupil_b_ = pupil_b;
    }
};

bool isBipartiteGraph(
    int curr_pupil,
    int curr_color,
    vector<vector<int>>& adj_list,
    vector<int>& color,
    vector<int>& vis
) {
    vis[curr_pupil] = 1;
    color[curr_pupil] = curr_color;

    for (int next_pupil : adj_list[curr_pupil]) {
        if (vis[next_pupil] == 0) {
            bool isBipartite = isBipartiteGraph(
                next_pupil,
                (curr_color + 1) % 2,
                adj_list,
                color,
                vis
            );

            if (!isBipartite) {
                return false;
            }
        } else {                                                // vis[i] = {1,2}, back-edge or cross-edge
            if (color[curr_pupil] == color[next_pupil]) {
                return false;
            }
        }
    }

    vis[curr_pupil] = 2;

    return true;
};

void solve(int pupil_cnt, vector<Friendship>& friendships, int friendship_cnt) {
    vector<vector<int>> adj_list(pupil_cnt+1, vector<int>());
    for (auto& [ pupil_a, pupil_b ] : friendships) {
        adj_list[pupil_a].push_back(pupil_b);
        adj_list[pupil_b].push_back(pupil_a);
    }

    vector<int> color(pupil_cnt+1, 0);
    vector<int> vis(pupil_cnt+1, 0);

    bool isBipartite = true;
    for (int i = 1; i <= pupil_cnt && isBipartite; i++) {
        if (vis[i] == 0) {
            isBipartite = isBipartiteGraph(i, 0, adj_list, color, vis);    
        }
    }

    if (!isBipartite) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i = 1; i <= pupil_cnt; i++) {
            cout << (color[i]+1) << " ";
        }
        cout << endl;
    };
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int pupil_cnt, friendship_cnt;
    cin >> pupil_cnt >> friendship_cnt;

    int pupil_a, pupil_b;
    vector<Friendship> friendships;
    for (int i = 0; i < friendship_cnt; i++) {
        cin >> pupil_a >> pupil_b;
        friendships.emplace_back(pupil_a, pupil_b);
    }

    solve(pupil_cnt, friendships, friendship_cnt);
    
    return 0;
}