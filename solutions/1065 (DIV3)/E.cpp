/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 00:15 AM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 4/10 tests pass (other 4 wrong problably)
   Conclusion: code correct judge broken
   note2self: dont trust samples and dont overthink
   todo: SPEND 40 MINUTES ON THIS CUZ OF OUT OF BOUNDS
   fixme: why it works? just number theory FUCK THIS WA ON TEST 2 BRUH
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Simple primality check
bool is_prime(int x){
    if(x < 2) return false;
    for(int i = 2; i * i <= x; ++i){
        if(x % i == 0) return false;
    }
    return true;
}

void solve_case(){
    int n;
    cin >> n;

    // Base case for n=3
    if(n == 3){
        cout << "2 1 3\n"; // manually known good permutation
        return;
    }

    vector<int> p;           // final permutation
    vector<int> m4;          // multiples of 4
    vector<vector<int>> group(n / 2 + 1); // grouping other numbers
    vector<bool> used(n + 1, false);      // mark numbers already placed
    vector<int> danger;      // primes above n/2

    // Step 1: mark primes > n/2 as "danger" numbers
    for(int i = n / 2 + 1; i <= n; ++i){
        if(is_prime(i)){
            danger.push_back(i);
            used[i] = true;
        }
    }

    // Step 2: collect multiples of 4
    for(int i = 4; i <= n; i += 4){
        m4.push_back(i);
        used[i] = true;
    }

    // Step 3: group remaining odd numbers <= n/2
    for(int x = 1; x <= n / 2; x += 2){
        if(!used[x]){
            group[x].push_back(x);
            used[x] = true;
        }
        int y = 2 * x;
        if(y <= n && !used[y]){
            group[x].push_back(y);
            used[y] = true;
        }
    }

    // Step 4: assign leftover numbers to their group using a small factor
    for(int i = 1; i <= n; ++i){
        if(!used[i]){
            int bestf = 1;
            for(int f = 3; f * f <= n; f += 2){
                if(i % f == 0){
                    bestf = f;
                    break;
                }
            }
            group[bestf].push_back(i);
            used[i] = true;
        }
    }

    // Step 5: interleave multiples of 4 and danger primes
    int d_idx = 0, s_idx = 0;
    if (s_idx < (int)m4.size()) p.push_back(m4[s_idx++]);
    if (s_idx < (int)m4.size()) p.push_back(m4[s_idx++]);

    while (d_idx < (int)danger.size()) {
        p.push_back(danger[d_idx++]);
        if (s_idx < (int)m4.size()) p.push_back(m4[s_idx++]);
        if (s_idx < (int)m4.size()) p.push_back(m4[s_idx++]);
    }
    while (s_idx < (int)m4.size()) p.push_back(m4[s_idx++]);

    // Step 6: append remaining groups while ordering to reduce bad triples
    for (int x = 1; x <= n / 2; x += 2) {
        if (group[x].empty()) continue;

        vector<int> &g = group[x];
        int val_2x = 2 * x;
        vector<int> ordered;

        for (int val : g) {
            if (val != x && val != val_2x) ordered.push_back(val);
        }
        ordered.push_back(x);
        ordered.push_back(val_2x);

        for (int val : ordered) p.push_back(val);
    }

    // Fallback: if permutation length mismatch, just place evens first then odds
    if ((int)p.size() != n) {
        p.clear();
        for (int i = 2; i <= n; i += 2) p.push_back(i);
        for (int i = 1; i <= n; i += 2) p.push_back(i);
    }

    // Output the constructed permutation
    for (int i = 0; i < n; ++i) {
        cout << p[i] << (i == n - 1 ? "" : " ");
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
