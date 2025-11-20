/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 11:50 PM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 10/10 tests pass (probably)
   Conclusion: code correct judge broken
   note2self: dont trust samples
   todo: find segfault (somewhere)
   fixme: Ajisai is spelled with s not z..
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve_case(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    for(int i = 0; i < n; ++i)
        cin >> b[i];

    /*
        Key Observation:
        A swap at index i flips a[i] and b[i].
        XOR score difference depends only on whether a[i] != b[i].

        At index i:
         - If a[i] == b[i], swapping does nothing.
         - If a[i] != b[i], swapping flips which player gets 1 in their XOR.

        Which player can act at position i?
         - Odd i → Ajisai's move.
         - Even i → Mai's move.

        So each index where a[i] != b[i] is a "critical position":
        whoever controls that turn can decide the XOR contribution.
    */

    vector<int> critical_indices;
    for(int i = 0; i < n; ++i){
        if(a[i] != b[i])
            critical_indices.push_back(i + 1); 
        // store 1-based index, since parity decides the player
    }

    int temp = critical_indices.size();

    /*
        If the number of critical positions is EVEN:
            Ajisai and Mai control the same number of index flips.
            Optimal play means both can counter each other perfectly.
            → Result is always Tie.

        If the number is ODD:
            The player who moves last on the LAST critical index wins.

        Since we stored indices in increasing order,
        the last element of critical_indices is the final contested move.
    */
    if(temp % 2 == 0){
        cout << "Tie\n";
        return;
    }

    int last_move = critical_indices.back();

    /*
        If last critical index is odd → Ajisai controls final decisive move.
        If last critical index is even → Mai controls final decisive move.
    */
    if(last_move % 2 != 0)
        cout << "Ajisai\n";
    else
        cout << "Mai\n";
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
