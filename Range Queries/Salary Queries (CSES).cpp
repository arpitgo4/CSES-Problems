// Salary Queries (CSES)

#include <vector>

using namespace std;
using ll = long long;

class SegmentTree {
private:
    tuple<ll,ll,ll> build(int l, int h, int i) {
        if (l == h)
            return ST[i] = { A[l], A[l], 1 };
        
        int m = (h-l)/2 + l;
        tuple<ll,ll,ll> A = build(l, m, 2*i+1);
        tuple<ll,ll,ll> B = build(m+1, h, 2*i+2);

        return ST[i] = {
            min(get<0>(A), get<0>(B)),
            max(get<1>(A), get<1>(B)),
            get<2>(A) + get<2>(B)
        };
    }

    ll query(int l, int h, int i, int lower, int upper) {
        if (l > h)
            return 0;

        int curr_l, curr_u, curr_count;
        tie(curr_l, curr_u, curr_count) = ST[i];
        if (l == h && (curr_l == lower && curr_u == upper))
            return curr_count;
        
        int m = (h-l)/2 + l;

        if (lower <= curr_u && upper <= curr_u)
            return query(l, m, 2*i+1, lower, upper);
        else if (lower > curr_u && upper > curr_u)
            return query(m+1, h, 2*i+2, lower, upper);

        return query(l, m, 2*i+1, lower, curr_u) + query(m+1, h, 2*i+2, curr_u+1, upper);
    }

    tuple<ll,ll,ll> update(int l, int h, int i, int idx, int val) {
        if (l == h && l == idx) {
            A[idx] = val;
            return ST[i] = { val, val, 1 };
        }

        int m = (h-l)/2 + l;

        tuple<ll,ll,ll> A, B;
        if (idx <= m) {
            A = update(l, m, 2*i+1, idx, val);
            B = ST[2*i+2];
        } else {        // val > upper
            A = ST[2*i+1];
            B = update(m+1, h, 2*i+2, idx, val);
        }

        return ST[i] = {
            min(get<0>(A), get<0>(B)),
            max(get<1>(A), get<1>(B)),
            get<2>(A) + get<2>(B)
        };
    }
public:

    int N;
    vector<ll> A;
    vector<tuple<ll,ll,ll>> ST;
    SegmentTree(vector<ll>& V) {
        A = V;
        N = A.size();
        ST.resize(4*N);
        build(0, N-1, 0);
    }

    ll query(int lower, int upper) {
        return query(0, N-1, 0, lower, upper);
    }

    tuple<ll,ll,ll> update(int i, int val) {
        return update(0, N-1, 0, i, val);
    }

    void print_segment_tree() {
        cout << "Original Array: " << endl;
        for (int a : A)
            cout << a << ", ";
        cout << endl;

        cout << "Segment Tree: " << endl;
        for (tuple<ll,ll,ll> t : ST) {
            int l, h, count;
            tie(l,h,count) = t;
            cout << "lower: " << l << ", higher: " << h << ", count: " << count << endl; 
        }
        cout << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    SegmentTree sg(A);

    sg.print_segment_tree();

    char c;
    int l, h;
    for (int i = 0; i < Q; i++) {
        cin >> c >> l >> h;
        if (c == '!') {
            sg.update(l-1, h);
            sg.print_segment_tree();
        }
        else 
            cout << sg.query(l, h) << endl;
    }

    return 0;
}