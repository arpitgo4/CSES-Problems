// Counting Coprime Pairs (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O()
// Space: O()

vector<int> prime_factorize(int num) {
    vector<int> factors(sqrt(num) + 1, 0);
    for (int x = 2; x*x <= num; x++) {
        while (num % x == 0) {
            factors[x]++;
            num /= x;
        }
    }

    if (num > 1)
        factors.push_back(num);

    return factors;
}

vector<int> euler_totient_sieve(int num) {
    vector<int> sieve(num+1, 0);
    sieve[1] = 1;
    for (int x = 2; x*x <= num; x++) {
        if (sieve[x])
            continue;
        
    }

    return sieve;
}

void solve(vector<int>& A, int N) {
    
    // Approach
    // 1. Can find euler's totient function for each number in array, Time: O(N√N)
    // 2. Filter numbers in array with above count [X, no can do...!!]

    // Approach
    // 1. Calculate euler's totient function table upto max number in array, Time: O(N√N)
    // 2. Sort & Filter numbers in array with above table for each number

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