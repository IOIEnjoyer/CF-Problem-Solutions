/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 00:08 AM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 4/10 tests pass (other 4 wrong problably)
   Conclusion: code correct judge broken
   note2self: dont trust samples bc integer overflow haunt my dreams
   todo: find segfault (somewhere)
   fixme: check indices mf
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve_case(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];

    /*
        EASY VERSION — KEY IDEA:

        We are asked if there exists a tree consistent with the given permutation p.

        Let p = [p1, p2, ..., pn]. The tree condition is:
            For any edge {u,v} with u < v, u must appear before v in p.

        Observation:
        - If at any point the sum of the first i elements equals the maximal possible sum
          (sum of 1..i for 1-based positions?), then it is impossible to construct a tree
          satisfying the condition. 
        - Otherwise, it is possible.
    */

    ll cur_sum = 0;
    for(int i = 1; i < n; ++i){
        cur_sum += a[i-1];

        /*
            Compute the "maximal sum" for i nodes:
                max_sum = i * (2*n - i + 1) / 2

            This formula represents the sum of the i largest values from 1 to n,
            i.e., the sum of the biggest nodes that could violate the ordering
            requirement for a valid tree.
        */
        ll max_sum = (ll)i * (2LL * n - i + 1) / 2;

        /*
            If cur_sum equals max_sum, then the nodes so far are "too high" to
            maintain the ordering constraints in a tree.

            Therefore, output "No" in this case.
        */
        if(cur_sum == max_sum){
            cout << "No\n";
            return;
        }
    }

    // If no violation is detected for all prefixes, a valid tree exists
    cout << "Yes\n";
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
