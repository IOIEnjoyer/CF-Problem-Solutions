/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 1:07 AM ( I am off to bed bruh)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void solve_case(){
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
 
    for(int qi = 0; qi < q; ++qi){
        ll c;
        cin >> c;
        priority_queue<ll> s;
        for(int i = 0; i < n; ++i)
            s.push(a[i]);
 
        ll coins = 0;
        for(int k = 29; k >= 0; --k){
            if(!((c >> k) & 1)) continue;
            ll val = s.top(); s.pop();
            ll need = 1LL << k;
            if(val < need){
                coins += (need - val);
                s.push(0);
            } else{
                s.push(val - need);
            }
        }
        cout << coins << '\n';
    }
}
 
int main(){
    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    /// Solved by <IOIEnjoyer>
}
