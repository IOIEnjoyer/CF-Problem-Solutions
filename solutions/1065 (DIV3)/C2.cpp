/*
   Author: IOIEnjoyer (Researcher - Algorithms & ML) — Japan
   Created: 00:01 AM (or when i actually wrote this)
   Remark: if compile = genius, if not = compiler hate me
   Hypothesis: O(nlogn) but O(n^2) pass so whatever
   Method: tried greedy -> nope. tried dp -> also nope. copied tourist's template -> kinda works??
   Results: 4/10 tests pass (other 6 wrong problably)
   Conclusion: code correct judge broken
   note2self: dont trust samples
   todo: find segfault (somewhere)
   fixme: Ajisai is spelled with s not z.. ensure 1-based indexing is respected or i will cry
   GitHub: https://github.com/IOIEnjoyer/CF-Problem-Solutions/tree/main
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve_case(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    for(int i = 0; i < n; ++i)
        cin >> b[i];

    /*
        HARD VERSION — KEY IDEA:

        The final result depends on:
            XOR(a[]) vs XOR(b[])

        Let:
            Xa = a1 ⊕ a2 ⊕ ... ⊕ an
            Xb = b1 ⊕ b2 ⊕ ... ⊕ bn

        Swapping a[i] with b[i] toggles whether bit contributions from that index
        go into Xa or Xb.

        Define:
            diff = Xa ⊕ Xb = XOR over all (a[i] ⊕ b[i])

        If diff == 0:
            Then Xa == Xb no matter what, so the game is ALWAYS a tie.
            Both players can mirror each other’s moves.

        If diff != 0:
            The winner is determined by the highest bit k where diff has a 1.
            The player who controls the *last index* where a[i][k] != b[i][k]
            can force that bit to favor them.

        Therefore:
            1. Find msb (most significant bit) where diff has 1.
            2. Scan from rightmost index backward to find last index i
               where bit_k of a[i] != bit_k of b[i].
            3. If that index is odd → Ajisai controls it → Ajisai wins.
               If even → Mai wins.
    */

    // Compute global XOR difference
    int x = 0;
    for(int i = 0; i < n; ++i)
        x ^= (a[i] ^ b[i]);

    // If total XOR difference is 0 → always Tie
    if(x == 0){
        cout << "Tie\n";
        return;
    }

    // Find highest bit where diff (x) differs
    int msb = -1;
    for(int k = 20; k >= 0; --k){
        if((x >> k) & 1){
            msb = k;
            break;
        }
    }

    /*
        Now locate the RIGHTMOST index i (1-based) where
        the msb-th bit of a[i] != msb-th bit of b[i].

        This index is the last “critical move”.

        - If it's odd → Ajisai controls it → Ajisai wins.
        - If it's even → Mai controls it → Mai wins.
    */
    int last_critical = -1;
    for(int i = n - 1; i >= 0; --i){
        int bita = (a[i] >> msb) & 1;
        int bitb = (b[i] >> msb) & 1;

        if(bita != bitb){
            last_critical = i + 1;  // convert to 1-based indexing
            break;
        }
    }

    // Determine winner based on parity of the last critical move
    if(last_critical % 2 != 0)
        cout << "Ajisai\n";   // odd index → Ajisai's turn
    else
        cout << "Mai\n";      // even index → Mai's turn
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
