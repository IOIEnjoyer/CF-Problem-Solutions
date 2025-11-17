/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 8:09 PM (or when i acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    cin >> s;
    int cnt[10] = {0};
    for(char c : s) cnt[c-'0']++;

    for(int i = 1; i <= 9; ++i) {
        if(cnt[i] > 0) {
            cout << char('0' + i);
            cnt[i]--;

            for(int d = 0; d < cnt[0]; ++d) cout << '0';

            for(int k = 1; k <= 9; ++k)
                for(int j = 0; j < cnt[k]; ++j)
                    cout << char('0' + k);

            cout << '\n';
            return 0;
        }
    }
  /// solved by <IOIEnjoyer>
}
