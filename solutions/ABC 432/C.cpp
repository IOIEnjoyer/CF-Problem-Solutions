/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 8:16 PM (or when i acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int NMAX = 2 * 1e5;
ll a[NMAX + 1];

int main() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];

    ll dif = y - x;
    ll reminder = (a[1] * x) % dif;
    for(int i = 2; i <= n; ++i){
        if((a[i] * x) % dif != reminder){
            cout << -1;
            return 0;
        }
    }
    
    ll left = 0,right = -1;
    for(int i = 1; i <= n; ++i){
        ll cur_min_w = a[i] * x;
        ll cur_max_w = a[i] * y;
        if(cur_min_w > left){
            left = cur_min_w;
        }
        if(right == -1 || cur_max_w < right){
            right = cur_max_w;
        }
    }
    
    if(left > right){
        cout << -1;
        return 0;
    }

    ll w_max = right - (right % dif - reminder + dif) % dif;

    if(w_max < left){
        cout << -1;
        return 0;
    }

    ll ans = 0;
    for(int i = 1; i <= n; ++i){
        ans += (w_max - a[i] * x) / dif;
    }
    cout << ans;
  /// solved by <IOIEnjoyer>
}
}
