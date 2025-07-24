// Mail Delivery (CSES)
 
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
// Euler's Tour

using graph_t = vector<vector<int>>;

class Street {
public:
    int crossing_1_;
    int crossing_2_;
    Street(int crossing_1, int crossing_2) {
        crossing_1_ = crossing_1;
        crossing_2_ = crossing_2;
    }
};

void solve(
    int crossing_cnt,
    vector<Street>& streets,
    int street_cnt
) {
    graph_t adj_list(crossing_cnt+1, vector<int>());
    for (auto& [ crossing_1, crossing_2 ] : streets) {
        adj_list[crossing_1].push_back(crossing_2);
        adj_list[crossing_2].push_back(crossing_1);
    }

    
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int crossing_cnt, street_cnt;
    cin >> crossing_cnt >> street_cnt;

    int crossing_1, crossing_2;
    vector<Street> streets;
    for (int i = 0; i < street_cnt; i++) {
        cin >> crossing_1 >> crossing_2;
        streets.emplace_back(crossing_1, crossing_2);
    }

    solve(crossing_cnt, streets, street_cnt);
    
    return 0;
}