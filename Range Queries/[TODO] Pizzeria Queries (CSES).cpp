// Pizzeria Queries (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N + QlogN)
// Space: O(N)
 
typedef long long ll;

vector<ll> A;

void build_seg_tree(int l, int h, int i) {

}

void update(int l, int h, int i, int k, int x) {

}

ll query(int l, int h, int i, int k) {
    return -1;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    cin >> N >> Q;
    
    A.assign(N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    build_seg_tree(0, N-1, 0);

    int type, k, x;
    for (int i = 0; i < Q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> k >> x;
            update(0, N-1, 0, k, x);
        } else {
            cin >> k;
            int val = query(0, N-1, 0, k);
            cout << val << endl;
        }
    }
    
    return 0;
}