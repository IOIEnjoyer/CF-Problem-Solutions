/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 11:27 PM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 10/10 tests pass (probably)
   Conclusion: code correct judge broken
   note2self: dont trust samples
   todo: find segfault (somewhere)
   fixme: why it works? no clue, just vibes
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
    For a given number of legs n, we want to count how many pairs (chickens, cows) exist
    such that:

        chickens * 2 + cows * 4 = n

    Let c = number of cows.
    Then chickens = (n - 4c) / 2 must be a non-negative integer.

    - n must be even; otherwise no solution exists.
    - c can range from 0 up to floor(n / 4).
    - For every valid c, the number of chickens is uniquely determined.

    Therefore:
        number of configurations = floor(n / 4) + 1
*/

void solve_case(){
    int n;
    cin >> n;

    // If n is odd, no combination of 2 and 4 can sum to n.
    if(n % 2 != 0){
        cout << 0 << '\n';
        return;
    }

    // Maximum number of cows possible (each contributes 4 legs)
    int max_cow = n / 4;
    // From 0 cows to max_cow, inclusive → max_cow + 1 configurations
    int ans = max_cow + 1;

    cout << ans << '\n';
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    /// solved by <IOIEnjoyer>
}
