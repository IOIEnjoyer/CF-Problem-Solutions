/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 11:37 PM (or when i actually wrote this)
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

void solve_case(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    /*
        We want to minimize |b1 + b2 + ... + b(n-1)|.

        But:
            b1 + ... + b(n-1) = (a2 - a1) + (a3 - a2) + ... + (an - a(n-1))
                              = an - a1

        So the entire objective reduces to minimizing |an - a1|.
        
        The middle values a[1..n-2] DO NOT affect the cost at all.
        Therefore, for lexicographical minimality, we set every middle -1 to 0.
    */
    for (int i = 1; i < n - 1; ++i) {
        if (a[i] == -1) {
            a[i] = 0;  // lexicographically smallest choice
        }
    }

    /*
        Now we need to set a[0] and a[n-1].

        Four cases:
         1) both endpoints known → nothing to fix.
         2) a[0] known, a[n-1] = -1 → best is to match endpoints: a[n-1] = a[0].
         3) a[0] = -1, a[n-1] known → symmetric: a[0] = a[n-1].
         4) both endpoints = -1 → lexicographically smallest is 0 and 0.

        Matching endpoints minimizes |an - a1| = 0 whenever possible.
    */
    if (a[0] != -1 && a[n-1] != -1) {
        // both endpoints already fixed, nothing needed
    }
    else if (a[0] != -1 && a[n-1] == -1) {
        a[n-1] = a[0];  // minimize |an - a1|
    }
    else if (a[0] == -1 && a[n-1] != -1) {
        a[0] = a[n-1];  // minimize |an - a1|
    }
    else {
        // both unknown → lexicographically smallest choice
        a[0] = 0;
        a[n-1] = 0;
    }

    /*
        The minimized value is simply |a[n-1] - a[0]|.
        Then we output the constructed lexicographically smallest array.
    */
    cout << abs(a[n-1] - a[0]) << '\n';
    for (int i = 0; i < n; ++i) {
        cout << a[i] << (i == n - 1 ? "" : " ");
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    /// solved by <IOIEnjoyer>
}
