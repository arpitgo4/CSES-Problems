// Distinct Values Queries (CSES)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time: O(NlogN)
// Space: O(NlogN)

class Node {
public:
    int distVals;

    Node() {}

    Node(int val) {
        distVals = (1 << val-1);
    }

    static Node* merge(Node* n1, Node* n2) {
        Node* mergedNode = new Node();
        mergedNode->distVals = n1->distVals | n2->distVals;
        return mergedNode;
    }
};

class SegmentTree {
private:

    // Time: O(NlogN)
    // Space: O(logN)
    Node* build(int l, int r, int i) {
        if (l == r)
            return ST[i] = new Node(A[l]);

        int m = (r-l)/2 + l;
        Node* left = build(l, m, 2*i+1);
        Node* right = build(m+1, r, 2*i+2);

        return ST[i] = Node::merge(left, right);
    }

    // Time: O(NlogN)
    // Space: O(logN)
    Node* _query(int l, int r, int i, int p, int q) {
        if (l > r)
            return nullptr;
        if (l == r)
            return ST[i];

        int m = (r-l)/2 + l;
        if (p <= m && q <= m)
            return _query(l, m, 2*i+1, p, q);
        else if (p > m && q > m)
            return _query(m+1, r, 2*i+2, p, q);

        Node* left = _query(l, m, 2*i+1, p, m);
        Node* right = _query(m+1, r, 2*i+2, m+1, q);

        return Node::merge(left, right);
    }

public:

    int N;
    vector<int> A;
    vector<Node*> ST;
    SegmentTree(vector<int>& OA) {
        A = OA;
        N = A.size();
        ST.assign(4*N, 0);
        build(0, N-1, 0);
    }

    int query(int l, int r) {
        Node* res = _query(0, N-1, 0, l, r);
        return __builtin_popcount(res->distVals);
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

    SegmentTree sg(A);

    int l, r;
    for (int i = 0; i < Q; i++) {
        cin >> l >> r;
        cout << sg.query(l-1, r-1) << endl;
    }   
    
    return 0;    
}