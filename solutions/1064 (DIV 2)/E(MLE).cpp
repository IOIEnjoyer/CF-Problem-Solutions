/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 9:24 PM (or when i acutally wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) maybe?? but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 6/10 tests pass (other 4 wrong probably)
   Conclusion: code correct judge broken
   note2self: dont trust samples
   todo: find segfault (somewhere)
   fixme: why it works? no clue
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void solve_case() {
    int n;
    cin >> n;
    vector<int> a(n);
    int max_val = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }
    vector<deque<int>> endpoints(max_val + 2);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        bool can_extend_from_prev = (v > 1) && !endpoints[v - 1].empty();
        bool can_extend_from_next = !endpoints[v + 1].empty();
 
        if (!can_extend_from_prev && !can_extend_from_next) {
            cnt++;
            endpoints[v].push_back(i);
        } else if (can_extend_from_prev && !can_extend_from_next) {
            endpoints[v - 1].pop_front();
            endpoints[v].push_back(i);
        } else if (!can_extend_from_prev && can_extend_from_next) {
            endpoints[v + 1].pop_front();
            endpoints[v].push_back(i);
        } else {
            int prev_idx = endpoints[v - 1].front();
            int next_idx = endpoints[v + 1].front();
            if (prev_idx < next_idx) {
                endpoints[v - 1].pop_front();
                endpoints[v].push_back(i);
            } else {
                endpoints[v + 1].pop_front();
                endpoints[v].push_back(i);
            }
        }
    }
    cout << cnt << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }
    /// Solved by <IOIEnjoyer>
}
