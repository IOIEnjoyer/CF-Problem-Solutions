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
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    char target_char = s.back();
 
    for(int i = 0; i < n; ++i){
        if(s[i] != target_char)
            cnt++;
    }
    cout << cnt << '\n';
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
