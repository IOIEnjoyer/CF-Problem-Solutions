/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 02:43 AM (or when I acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void solve_case(){
    ll a,b,n;
    cin >> a >> b >> n;
    ll k = a / b;
 
    if(b == 0){
        cout << n << '\n';
        return;
    }
    if(n <=k){
        cout << 1 << '\n';
    } else{
        if(a == b){
            cout << 1 << '\n';
        } else if(n == k + 1){
            if((b * n) % a == 0){
                cout << 1 << '\n';
            } else{
                cout << 2 << '\n';
            }
        } else{
          cout << 2 << '\n';
        }
    }
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
