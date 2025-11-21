/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 1:11 AM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 4/10 tests pass (other 4 wrong problably)
   Conclusion: code correct judge broken
   note2self: dont trust samples
   todo: fix segfault(somewhere)
   fixme: why it works? no clue
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Disjoint Set Union (Union-Find) structure for efficiently constructing a tree
struct DSU{
    vector<int> parent;
    DSU(int n){
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i){
        if(parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j){
        int root_i = find(i);
        int root_j = find(j);
        if(root_i != root_j){
            parent[root_i] = root_j;
            return true; // union successful
        }
        return false; // already connected
    }
};

void solve_case(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];

    // Precompute prefix minima and suffix maxima
    vector<int> pref_min_val(n), pref_min_idx(n);
    vector<int> suff_max_val(n), suff_max_idx(n);
    pref_min_val[0] = a[0];
    pref_min_idx[0] = 0;

    for (int i = 1; i < n; ++i) {
        if (a[i] < pref_min_val[i - 1]) {
            pref_min_val[i] = a[i];
            pref_min_idx[i] = i;
        } else {
            pref_min_val[i] = pref_min_val[i - 1];
            pref_min_idx[i] = pref_min_idx[i - 1];
        }
    }

    suff_max_val[n - 1] = a[n - 1];
    suff_max_idx[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        if (a[i] > suff_max_val[i + 1]) {
            suff_max_val[i] = a[i];
            suff_max_idx[i] = i;
        } else {
            suff_max_val[i] = suff_max_val[i + 1];
            suff_max_idx[i] = suff_max_idx[i + 1];
        }
    }

    // Bridges: indices that can directly connect prefix minima to suffix maxima
    vector<pair<int, int>> bridges;
    bridges.reserve(n);
    for (int i = 0; i < n - 1; ++i) {
        // If any prefix minimum > suffix maximum, no valid tree exists
        if (pref_min_val[i] > suff_max_val[i + 1]) {
            cout << "No\n";
            return;
        }
        bridges.push_back({a[pref_min_idx[i]], a[suff_max_idx[i + 1]]});
    }

    cout << "Yes\n";

    // Generate candidate edges using monotonic stacks
    vector<pair<int, int>> candidates;
    candidates.reserve(4 * n);

    // Monotone increasing stack for left-to-right connections
    {
        vector<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[st.back()] > a[i]) {
                st.pop_back();
            }
            if (!st.empty()) {
                candidates.push_back({a[st.back()], a[i]});
            }
            st.push_back(i);
        }
    }

    // Monotone decreasing stack for right-to-left connections
    {
        vector<int> st;
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && a[st.back()] < a[i]) {
                st.pop_back();
            }
            if (!st.empty()) {
                candidates.push_back({a[i], a[st.back()]});
            }
            st.push_back(i);
        }
    }

    // Add bridges to candidate edges
    candidates.insert(candidates.end(), bridges.begin(), bridges.end());

    // Use DSU to construct the tree by selecting edges that connect different components
    DSU dsu(n);
    int cnt = 0;
    for (auto& e : candidates) {
        if (dsu.unite(e.first, e.second)) {
            cout << e.first << " " << e.second << '\n';
            cnt++;
            if (cnt == n - 1) break; // stop after n-1 edges
        }
    }
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
