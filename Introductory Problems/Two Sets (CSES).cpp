// Two Sets (CSES)

#include <iostream>

using namespace std;

// Time: O(N^2)
// Space: O(N^2)

vector<vector<int>> cache;

bool dfs(int i, int sum, int k, int N, vector<int>& acc) {
    if (i > N)
        return sum == k;
    if (cache[i][sum] != -1)
        return cache[i][sum];

    acc.push_back(i);
    bool res1 = dfs(i+1, sum+i, k, N, acc);
    if (res1 == true)
        return res1;

    acc.pop_back();
    bool res2 = dfs(i+1, sum, k, N, acc);
    if (res2 == true)
        return res2;
}

void solve(int N) {
    cache.assign(N+1, vector<int>(N+1, -1));

    // can do in O(1), with AP sum formula
    int sum = 0;
    for (int i = 1; i <= N; i++)
        sum += i;

    if (sum % 2 != 0) {
        cout << "NO";
        return;
    }

    int k = sum/2;
    vector<int> acc;
    bool res = dfs(1, 0, k, N, acc);

    if (res == false) {
        cout << "NO";
    } else {
        cout << "YES" << endl;
        unordered_set<int> uSet;
        cout << acc.size() << endl;
        for (int a : acc) {
            cout << a << " ";
            uSet.insert(a);
        }
        cout << endl;

        cout << N-acc.size() << endl;
        for (int i = 1; i <= N; i++) {
            if (uSet.find(i) == uSet.end())
                cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    solve(N);

    return 0;
}