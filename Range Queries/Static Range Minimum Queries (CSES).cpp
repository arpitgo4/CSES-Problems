// Static Range Minimum Queries (CSES)
 
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class SparseTable {
public:
    SparseTable(vector<int>& OA) {
        A = OA;
        N = A.size();
        build(A);
    }

    int query(int l, int r) {
        return _query(l, r);
    }
private:

    int N;
    vector<int> A;
    vector<vector<int>> ST;

    // Time: O(NlogN)
    // Space: O(NlogN)
    void build(vector<int>& A) {
        int N = A.size();
        int maxPower = floor(log2(N)) + 1;
        ST.assign(maxPower, vector<int>(N, INT_MAX));

        for (int j = 0; j < N; j++)
            ST[0][j] = A[j];

        for (int powe = 1; powe < maxPower; powe++)
            for (int j = 0; j < N; j++) {
                int a = ST[powe-1][j];
                int b = INT_MAX;
                if (j + (1 << powe-1) < N)
                    b = ST[powe-1][j+(1 << powe-1)];

                ST[powe][j] = min(a, b);
            }
    }

    // Time: O(1)
    // Space: O(1)
    int _query(int l, int r) {
        int size = r-l+1;
        int powe = floor(log2(size));
        int a = ST[powe][l];
        int b = INT_MAX;
        if (r-(1 << powe)+1 >= l)
            b = ST[powe][r-(1 << powe)+1];
        return min(a, b);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    SparseTable sparseTable(A);

    int a, b;
    vector<pair<int,int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        queries[i] = { a, b };
    }

    for (int i = 0; i < Q; i++) {
        pair<int,int> q = queries[i];
        cout << sparseTable.query(q.first-1, q.second-1) << endl;
    }

    return 0;
}