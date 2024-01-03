// Counting Divisors (CSES)
 
#include <iostream>
#include <unordered_map>
#include <cmath>
 
using namespace std;
using ll = long long;
 
// Time: O(√num)
// Space: O(√num)

unordered_map<int,int> prime_count;

void count_primes(int num) {
    for (int x = 2; x*x <= num; x++) {
        while (num % x == 0) {
            num /= x;
            prime_count[x]++;
        }
    }

    if (num > 1)
        prime_count[num]++;
}

void solve(int num) {
    prime_count.clear();
    count_primes(num);

    ll num_divisors = 1;
    for (auto& p : prime_count)
        num_divisors *= (p.second+1);

    cout << num_divisors << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;

    int num;
    while (N--) {
        cin >> num;
        solve(num);
    }
    
    return 0;
}