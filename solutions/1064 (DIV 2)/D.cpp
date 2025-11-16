/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 12:07 AM
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: Don't trust sample test's
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int MOD = 998244353;
 
void solve_case() {
    int n;
    cin >> n;
    map<int, int> freqs;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        freqs[val]++;
    }
 
    vector<int> C;
    for (auto const& [val, num] : freqs) {
        C.push_back(num);
    }
    sort(C.rbegin(), C.rend());
    int m = C.size();
    ll total_valid_multisets = 0;
    if (m > 0) {
        vector<ll> dp_suf2(n + 1, 0);
        dp_suf2[0] = 1;
        int current_max_sum = 0;
 
        for (int i = 1; i < m; ++i) {
            int current_C = C[i];
            current_max_sum += current_C;
            for (int j = current_max_sum; j >= 0; --j) {
                if (j >= current_C) {
                    dp_suf2[j] = (dp_suf2[j] + (ll)current_C * dp_suf2[j - current_C]) % MOD;
                }
            }
        }
 
        ll ways_i1 = 0;
        for (int j = C[0]; j <= n; ++j) {
            ways_i1 = (ways_i1 + dp_suf2[j]) % MOD;
        }
        total_valid_multisets = (total_valid_multisets + ways_i1) % MOD;
    }
    vector<ll> pref_prod(m + 1, 1);
    for (int i = 0; i < m; ++i) {
        pref_prod[i + 1] = (pref_prod[i] * C[i]) % MOD;
    }
 
    vector<ll> suf_prod_plus_one(m + 2, 1);
    for (int i = m - 1; i >= 0; --i) {
        suf_prod_plus_one[i + 1] = (suf_prod_plus_one[i + 2] * (C[i] + 1)) % MOD;
    }
    for (int i = 2; i <= m; ++i) {
        ll ways_prefix = pref_prod[i - 1];
        ll ways_suffix = suf_prod_plus_one[i + 1];
        total_valid_multisets = (total_valid_multisets + (ways_prefix * ways_suffix) % MOD) % MOD;
    }
    total_valid_multisets = (total_valid_multisets + pref_prod[m]) % MOD;
    cout << total_valid_multisets << '\n';
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }
    /// solved by <IOIEnjoyer>
}
