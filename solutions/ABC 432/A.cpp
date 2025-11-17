/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 8:07 PM (or when i acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
   int a,b,c;
   cin >> a >> b >> c;
   int ans = 0;
   int v[] = {a,b,c};
   sort(v, v + 3, greater<int>());
   cout << (100 *v[0] + 10 * v[1] + v[2]);
  /// solved by <IOIEnjoyer>
}
