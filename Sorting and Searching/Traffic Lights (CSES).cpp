// Traffic Lights (CSES)

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <iterator>

using namespace std;

// Time: O(NlogN)
// Space: O(N)

void solve(int street_length, vector<int>& lights, int N) {
    set<int> passages;
    unordered_map<string, multiset<int>::iterator> passages_index;
    multiset<int> passages_length;

    passages.insert(0);
    passages.insert(street_length);
    auto p_len_itr = passages_length.insert(street_length);
    passages_index.insert({ 0 + "," + street_length, p_len_itr });

    for (int light : lights) {
        auto light_itr = passages.insert(light).first;
        int a = *prev(light_itr);
        int b = *next(light_itr);

        auto len_itr = passages_index[a + "," + b];
        passages_length.erase(len_itr);
        passages_index.erase(to_string(a) + "," + to_string(b));

        int a_len = light-a;
        auto a_itr = passages_length.insert(a_len);
        passages_index.insert({ a + "," + light, a_itr });

        int b_len = b-light;
        auto b_itr = passages_length.insert(b_len);
        passages_index.insert({ light + "," + b, b_itr });

        cout << *passages_length.rbegin() << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int street_length, N;
    cin >> street_length >> N;

    vector<int> lights(N);
    for (int i = 0; i < N; i++)
        cin >> lights[i];

    solve(street_length, lights, N);

    return 0;
}