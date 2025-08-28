// Book Shop (CSES)
 
#include <iostream>
#include <vector>
 
using namespace std;
 
// Time: O(N * K)
// Space: O(N * K)
 
/**
 * Knapsack DP
 */

class Book {
public:
    int price_;
    int page_cnt_;
    Book(int price) {
        price_ = price;
    }
};

int findMaxPagesBookSubset(
    int curr_book_idx,
    int money_left,
    vector<Book>& books,
    int book_cnt,
    vector<vector<int>>& dp
) {
    if (curr_book_idx == book_cnt || money_left == 0)
        return 0;
    if (dp[curr_book_idx][money_left] != -1)
        return dp[curr_book_idx][money_left];
    
    auto& [ price, page_cnt ] = books[curr_book_idx];
    int include_book__page_cnt = 0;
    if (money_left >= price) {
        include_book__page_cnt = page_cnt + findMaxPagesBookSubset(
            curr_book_idx+1,
            money_left-price,
            books,
            book_cnt,
            dp
        );
    }
    
    int exclude_book__page_cnt = findMaxPagesBookSubset(
        curr_book_idx+1,
        money_left,
        books,
        book_cnt,
        dp
    );

    return dp[curr_book_idx][money_left] = max(
        include_book__page_cnt,
        exclude_book__page_cnt
    );
}

void solve(
    vector<Book>& books,
    int book_cnt,
    int max_total_price
) {
    vector<vector<int>> dp(book_cnt, vector<int>(max_total_price+1, -1));
    int max_page_cnt = findMaxPagesBookSubset(
        0,
        max_total_price,
        books,
        book_cnt,
        dp
    );

    cout << max_page_cnt << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int book_cnt, max_total_price;
    cin >> book_cnt >> max_total_price;
    
    int price;
    vector<Book> books;
    for (int i = 0; i < book_cnt; i++) {
        cin >> price;
        books.emplace_back(price); 
    }

    int page_cnt;
    for (int i = 0; i < book_cnt; i++) {
        cin >> books[i].page_cnt_;
    }

    solve(
        books,
        book_cnt,
        max_total_price
    );
    
    return 0;
}