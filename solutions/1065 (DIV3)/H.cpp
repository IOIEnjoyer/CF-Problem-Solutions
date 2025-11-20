// NOTE: This is NOT my solution. This solution is adapted
// from another source and is very clever, using dynamic programming ideas.

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pb push_back
#define pii pair<int, int>
#define int ll  // use 64-bit integers

// Solve a single test case
void solve() {
    int n, m;
    cin >> n >> m;

    // ans[i] will store pairs {value of ai, -maximum sum of v(j, aj) up to i-th index}
    vector<vector<pii>> ans(n);

    // Base case: first element is always 1 with 0 sum
    ans[0] = {{1, 0}};

    for (int i = 1; i < n; i++) {
        int x = i + 1; // current position (since i is 0-indexed)
        vector<pii> sp;

        // Case 1: increment previous values by 1, ensuring strictly increasing array
        for (int j = 0; j < ans[i - 1].size(); j++) {
            if (ans[i - 1][j].first < m) {
                // -ans[i-1][j].second because we are storing negatives for easier max tracking
                sp.pb({ans[i - 1][j].first + 1, -ans[i - 1][j].second});
            }
        }

        // Case 2: take multiples of current index x, which contribute to v(x, ai)
        for (int j = x; j <= m; j += x) {
            int cnt = 0;
            int x2 = j;
            // Count power of x dividing j
            while (x2 % x == 0) {
                cnt++;
                x2 /= x;
            }

            // Find the largest previous element less than current j
            int ind = lower_bound(all(ans[i - 1]), make_pair(j, 0ll)) - ans[i - 1].begin() - 1;
            // Store value j and cumulative sum (-cnt - previous)
            sp.pb({j, -cnt - ans[i - 1][ind].second});
        }

        // Sort candidate pairs by value
        sort(all(sp));

        // Keep only the best (maximum sum) for increasing sequences
        int mx = 0;
        for (auto [val, y] : sp) {
            if (mx < -y) { // -y because stored as negative
                ans[i].pb({val, -y});
                mx = -y;
            }
        }
    }

    // Output the answer for the last element
    cout << ans[n - 1].back().second << "\n";
}

int32_t main() {
    cin.tie(0)->ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
