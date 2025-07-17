// Shortest Routes II (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
 
// Time: O(V^3)
// Space: O(V^2)
 
using ll_t = long long;

const ll_t INF = LLONG_MAX;

class Query {
public:
    int city_a_;
    int city_b_;
    Query(int city_a, int city_b) {
        city_a_ = city_a;
        city_b_ = city_b;
    }
};
class Road {
public:
    int road_end_1_;
    int road_end_2_;
    ll_t road_len_;
    Road(int road_end_1, int road_end_2, ll_t road_len) {
        road_end_1_ = road_end_1;
        road_end_2_ = road_end_2;
        road_len_ = road_len;
    }
};

void findAllPairsShortestPath(
    vector<vector<ll_t>>& adj_mat,
    int city_cnt
) {
    for (int inter = 1; inter <= city_cnt; inter++) {
        for (int city_a = 1; city_a <= city_cnt; city_a++) {
            for (int city_b = 1; city_b <= city_cnt; city_b++) {
                if (adj_mat[city_a][inter] != INF && adj_mat[inter][city_b] != INF) {
                    adj_mat[city_a][city_b] = min<ll_t>(
                        adj_mat[city_a][city_b],
                        adj_mat[city_a][inter] + adj_mat[inter][city_b]
                    );
                }
            }
        }
    }
}

void solve(
    int city_cnt,
    vector<Road>& roads,
    int road_cnt,
    vector<Query>& queries
) {
    vector<vector<ll_t>> adj_mat(city_cnt+1, vector<ll_t>(city_cnt+1, INF));
    for (int i = 0; i <= city_cnt; i++) {
        adj_mat[i][i] = 0;
    }

    for (auto& [ road_end_1, road_end_2, road_len ] : roads) {
        adj_mat[road_end_1][road_end_2] = min<ll_t>(
            adj_mat[road_end_1][road_end_2], 
            road_len
        );
        adj_mat[road_end_2][road_end_1] = min<ll_t>(
            adj_mat[road_end_2][road_end_1], 
            road_len
        );
    }

    findAllPairsShortestPath(
        adj_mat,
        city_cnt
    );

    for (auto& [city_a, city_b] : queries) {
        ll_t dist = adj_mat[city_a][city_b];
        cout << (dist == INF ? -1 : dist) << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int city_cnt, road_cnt, query_cnt;
    cin >> city_cnt >> road_cnt >> query_cnt;

    int road_end_1, road_end_2;
    ll_t road_len;
    vector<Road> roads;
    for (int i = 0; i < road_cnt; i++) {
        cin >> road_end_1 >> road_end_2 >> road_len;
        roads.emplace_back(road_end_1, road_end_2, road_len);
    }

    int city_a, city_b;
    vector<Query> queries;
    for (int i = 0; i < query_cnt; i++) {
        cin >> city_a >> city_b;
        queries.emplace_back(city_a, city_b);
    }

    solve(city_cnt, roads, road_cnt, queries);
    
    return 0;
}