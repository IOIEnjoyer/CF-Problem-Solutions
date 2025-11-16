/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 11:58 PM (or when I acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void solve_case(){
    int n;
    cin >> n;
    vector<ll> a(n);
    set<pair<ll, int>> s;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        s.insert({a[i],i});
    }
    if(n == 1){
        cout << 0 << '\n';
        return;
    }
    vector<int> prev_idx(n),next_idx(n);
    for(int i = 0; i < n; ++i){
        prev_idx[i] = (i - 1 + n) % n;
        next_idx[i] = (i + 1) % n;
    }
    ll total = 0;
    int cnt = 0;
    while(cnt < n - 1){
        auto it = s.begin();
        ll val = it->first;
        int idx = it->second;
        s.erase(it);
 
        int p_idx = prev_idx[idx];
        int n_idx = next_idx[idx];
 
        int merge_with_idx;
        if(a[p_idx] <= a[n_idx]){
            merge_with_idx = p_idx;
        } else{
            merge_with_idx = n_idx;
        }
        ll old_neighbor_val = a[merge_with_idx];
        ll cost = max(val,old_neighbor_val);
        total += cost;
 
        s.erase({old_neighbor_val,merge_with_idx});
        a[merge_with_idx] = cost;
        s.insert({a[merge_with_idx],merge_with_idx});
 
        next_idx[p_idx] = n_idx;
        prev_idx[n_idx]=p_idx;
        cnt++;
    }
    cout << total << '\n';
}
 
int main()
{
   int t;
   cin >> t;
   while(t--){
    solve_case();
   }
   /// Solved by <IOIEnjoyer>
}
