/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 9:03 PM (or when i acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_VAL = 500005;
template <typename T>
struct FenwickTree {
    int size;
    vector<T> tree;
    FenwickTree(int s) : size(s), tree(s + 1, 0) {}
    void update(int idx, T delta) {
        idx++;
        for (; idx <= size; idx += idx & -idx) {
            tree[idx] += delta;
        }
    }
    T query(int idx) {
        idx++;
        T sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }
};

int main() {
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    FenwickTree<ll> bit_count(MAX_VAL);
    FenwickTree<ll> bit_sum(MAX_VAL);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        bit_count.update(a[i], 1);
        bit_sum.update(a[i], a[i]);
    }

    for (int k = 0; k < q; ++k) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            ll y;
            cin >> x >> y;
            --x;
            bit_count.update(a[x], -1);
            bit_sum.update(a[x], -a[x]);
            a[x] = y;
            bit_count.update(a[x], 1);
            bit_sum.update(a[x], a[x]);
        } else {
            ll l, r;
            cin >> l >> r;
            if (l > r) {
                cout << (ll)n * l << '\n';
                continue;
            }
            ll count_less_l = (l > 0) ? bit_count.query(l - 1) : 0;
            ll part1 = count_less_l * l;
            ll sum_up_to_r = bit_sum.query(r);
            ll sum_less_l = (l > 0) ? bit_sum.query(l - 1) : 0;
            ll part2 = sum_up_to_r - sum_less_l;
            ll count_up_to_r = bit_count.query(r);
            ll part3 = (n - count_up_to_r) * r;

            cout << part1 + part2 + part3 << '\n';
        }
      /// solved by <IOIEnjoyer>
    }
}
