// Forest Queries (CSES)

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

// Time: O(N^2)
// Space: O(N^2)
// Query Time: Q * O(1) = O(Q)

vector<vector<int>> P;

// debugging
void print_matrix(vector<vector<int>> A, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

// Time: O(1)
int query(int i1, int j1, int i2, int j2) {
    return P[i2][j2] - P[i1-1][j2] - P[i2][j1-1] + P[i1-1][j1-1];
}

// Time: O(N^2)
void build_prefix_array(vector<vector<int>>& A, int N) {
    P.assign(N+1, vector<int>(N+1, 0));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            P[i][j] = A[i-1][j-1] + P[i-1][j] + P[i][j-1] - P[i-1][j-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> A(N, vector<int>(N, 0));
    char c;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> c;
            if (c == '*')
                A[i][j] = 1;
        }

    build_prefix_array(A, N);

    vector<int> res(Q);
    int i1, j1, i2, j2;
    for (int i = 0; i < Q; i++) {
        cin >> i1 >> j1 >> i2 >> j2;
        res[i] = query(i1, j1, i2, j2);
    }

    for (int r : res)
        cout << r << endl;

    return 0;
}