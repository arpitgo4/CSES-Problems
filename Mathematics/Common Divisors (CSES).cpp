// Common Divisors (CSES)
 
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
// Time: O(NloglogN) ~ O(N)
// Space: O(N)

void print_vector(vector<int>& A) {
    for (int a : A)
        cout << a << " ";
    cout << endl;
}

void solve(vector<int>& A, int N) {
    int l = 2;
    int h = *max_element(A.begin(), A.end());

    vector<int> divisors(h+1);
    for (int i = 0; i < h+1; i++)
        divisors[i] = i;

    for (int x = l; x <= h; x++)
        for (int j = 2*x; j <= h; j+=x)
            divisors[j] = x;

    print_vector(divisors);

    vector<int> count(h+1, 0);
    for (int d : divisors)
        count[d]++;

    print_vector(count);

    int max_divisor = 1;
    for (int a : A)
        if (count[divisors[a]] >= 2)
            max_divisor = max(max_divisor, divisors[a]);

    cout << max_divisor;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solve(A, N);
    
    return 0;
}