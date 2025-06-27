// Building Roads (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
 
using namespace std;
 
// Time: O(N * ⍺(M))
// Space: O(N)
 
using road_t = pair<int,int>;

class DisjointSet {
public:
    DisjointSet(int set_sz) {
        parent_.assign(set_sz+1, 0);
        iota(parent_.begin(), parent_.end(), 0);
        sz_.assign(set_sz+1, 1);
    }

    int root(int x) {
        if (parent_[x] != x) {
            parent_[x] = root(parent_[x]);
        }

        return parent_[x];
    }

    void union_set(int x, int y) {
        int root_x = root(x);
        int root_y = root(y);
        if (root_x != root_y) {
            if (sz_[root_x] < sz_[root_y])
                swap(root_x, root_y);

            parent_[root_y] = root_x;
            sz_[root_x] += sz_[root_y];
        }
    }

private:
    vector<int> parent_;
    vector<int> sz_;
};

void solve(int city_cnt, vector<road_t>& roads, int road_cnt) {
    DisjointSet roads_set(city_cnt);

    for (auto& [ road_end_1, road_end_2 ] : roads) {
        if (roads_set.root(road_end_1) != roads_set.root(road_end_2)) {
            roads_set.union_set(road_end_1, road_end_2);
        }
    }

    vector<road_t> required_roads;
    int prev_root = -1;
    for (int i = 1; i <= city_cnt; i++) {
        if (roads_set.root(i) == i) {
            if (prev_root != -1) {
                required_roads.push_back({ prev_root, i });
            }

            prev_root = i;
        }
    }

    cout << required_roads.size() << endl;
    for (auto& [ road_end_1, road_end_2 ] : required_roads) {
        cout << road_end_1 << " " << road_end_2 << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int city_cnt, road_cnt;
    cin >> city_cnt >> road_cnt;

    int road_end_1, road_end_2;
    vector<road_t> roads(road_cnt);
    for (int i = 0; i < road_cnt; i++) {
        cin >> road_end_1 >> road_end_2;
        roads[i] = { road_end_1, road_end_2 };
    }

    solve(city_cnt, roads, road_cnt);
    
    return 0;
}