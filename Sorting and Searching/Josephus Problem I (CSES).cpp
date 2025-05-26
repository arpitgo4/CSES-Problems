// Josephus Problem I (CSES)
 
#include <iostream>
#include <list>
#include <iterator>
 
using namespace std;
 
// Time: O(N)
// Space: O(N)
 
/**
 * We can use doubly-linked list here, as stepping 
 * function has constant time complexity.
 * 
 * Traversal from one number to next will take constant 
 * time and list provides constant time for delete operation.
 */
void solve(int children_cnt) {
    list<int> dbly_ll;
    for (int i = 1; i <= children_cnt; i++) {
        dbly_ll.push_back(i);
    }

    auto curr_itr = dbly_ll.begin();
    while (!dbly_ll.empty()) {
        curr_itr = next(curr_itr);
        if (curr_itr == dbly_ll.end())
            curr_itr = dbly_ll.begin();

        cout << (*curr_itr) << " ";
        curr_itr = dbly_ll.erase(curr_itr);

        if (curr_itr == dbly_ll.end())
            curr_itr = dbly_ll.begin();
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int children_cnt;
    cin >> children_cnt;

    solve(children_cnt);
    
    return 0;
}