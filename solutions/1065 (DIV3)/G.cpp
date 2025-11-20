/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 1:35 AM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 4/10 tests pass (other 4 wrong problably)
   Conclusion: i am so bad shoulve solved in 5
   note2self: dont trust samples
   todo: fix segfault(somewhere)
   fixme: why it works? no clue
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1000003;     // prime modulus for counting sequences
const int MAX_VAL = 1000005; // maximum factorial we might need

ll fact[MAX_VAL], inv[MAX_VAL];

// Modular exponentiation: computes (base^exp) % MOD
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while(exp) {
        if(exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// Precompute factorials and modular inverses modulo MOD
void precompute() {
    fact[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < MAX_VAL; i++) {
        if (i >= MOD) fact[i] = 0; // factorial modulo prime
        else fact[i] = (fact[i - 1] * i) % MOD;
    }

    // Modular inverse using Fermat's little theorem
    ll invLast = power(fact[MOD - 1], MOD - 2);
    inv[MOD - 1] = invLast;
    for (int i = MOD - 2; i >= 1; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

// Solve a single test case
void solve_case() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> b[i];

    ll min_ops = -1;
    ll total_ways = 0;

    // Iterate over all possible counts of "double all elements" operations (0..20)
    for(int k = 0; k <= 20; ++k) {
        vector<ll> stage_sums(k + 1, 0); // track contributions at each stage
        vector<vector<int>> cnt(k + 1);

        ll cur_inv_prod = 1;
        ll cur_cost = k; // initially count the "double all" operations
        bool possible = true;

        // Process each element
        for(int i = 0; i < n; ++i) {
            ll val_after = (ll)a[i] << k; // value after k doubles
            if(val_after > b[i]) {        // impossible if value exceeds target
                possible = false;
                break;
            }
            ll diff = b[i] - val_after;  // remaining increments needed
            ll c0 = diff >> k;           // number of +1 operations before doubling
            stage_sums[0] += c0;
            cur_cost += c0;
            cur_inv_prod = (cur_inv_prod * inv[c0]) % MOD;

            int rem = diff & ((1 << k) - 1); // remainder bits for staged operations
            for(int j = 1; j <= k; ++j) {
                int bit = (rem >> (k - j)) & 1;
                stage_sums[j] += bit;
                cur_cost += bit;
            }
        }

        if(!possible) break;

        // Count sequences for this k using factorials
        ll ways_for_k = cur_inv_prod;
        for(int j = 0; j <= k; ++j) {
            if(stage_sums[j] >= MOD) {
                ways_for_k = 0;
                break;
            }
            ways_for_k = (ways_for_k * fact[stage_sums[j]]) % MOD;
        }

        // Update minimum operations and sequence count
        if(min_ops == -1 || cur_cost < min_ops) {
            min_ops = cur_cost;
            total_ways = ways_for_k;
        } else if(cur_cost == min_ops) {
            total_ways = (total_ways + ways_for_k) % MOD;
        }
    }

    if(min_ops == -1)
        cout << "0 0\n"; // fallback if impossible
    else
        cout << min_ops << " " << total_ways << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute(); // prepare factorials and inverses
    int t;
    cin >> t;
    while(t--) {
        solve_case();
    }
    /// solved by <IOIEnjoyer>
}
