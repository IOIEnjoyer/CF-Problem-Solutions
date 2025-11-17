/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 9:18 PM (or when i acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using ll = long long;

struct Operation {
    int from, to;
    ll amount;
};
int n;
ll a[20];
ll b[20];
ll sum_b[1 << 20];
int pc[1 << 20];
int dp[1 << 20];
int parent_mask[1 << 20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    ll total_sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        total_sum += a[i];
    }
    if (total_sum % n != 0) {
        cout << -1 << '\n';
        return 0;
    }
    ll avg = total_sum / n;
    for (int i = 0; i < n; ++i) {
        b[i] = a[i] - avg;
    }

    for (int i = 1; i < (1 << n); ++i) {
        int lsb_idx = __builtin_ctz(i);
        int prev_mask = i ^ (1 << lsb_idx);
        pc[i] = pc[prev_mask] + 1;
        sum_b[i] = sum_b[prev_mask] + b[lsb_idx];
    }

    vector<int> zero_subsets;
    zero_subsets.reserve(1 << n);
    for (int i = 1; i < (1 << n); ++i)
        if (sum_b[i] == 0)
            zero_subsets.push_back(i);

    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    int FULL = (1 << n) - 1;
  
    for (int sub : zero_subsets) {
        int inv = FULL ^ sub;
        for (int rest = inv;; rest = (rest - 1) & inv) {
            int mask = sub | rest;
            if (dp[rest] != -1) {
                int val = dp[rest] + 1;
                if (val > dp[mask]) {
                    dp[mask] = val;
                    parent_mask[mask] = sub;
                }
            }
            if (rest == 0) break;
        }
    }

    int partitions = dp[FULL];
    cout << n - partitions << '\n';

    vector<Operation> ops;
    int current_mask = FULL;

    while (current_mask > 0) {
        int group_mask = parent_mask[current_mask];
        vector<pair<ll, int>> givers;
        vector<pair<ll, int>> receivers;

        for (int i = 0; i < n; ++i) {
            if ((group_mask >> i) & 1) {
                if (a[i] > avg) {
                    givers.push_back({a[i] - avg, i + 1});
                } else if (a[i] < avg) {
                    receivers.push_back({avg - a[i], i + 1});
                }
            }
        }
        int g_idx = 0, r_idx = 0;
        while (g_idx < givers.size() && r_idx < receivers.size()) {
            ll amount = min(givers[g_idx].first, receivers[r_idx].first);
            ops.push_back({givers[g_idx].second, receivers[r_idx].second, amount});
            givers[g_idx].first -= amount;
            receivers[r_idx].first -= amount;

            if (givers[g_idx].first == 0) g_idx++;
            if (receivers[r_idx].first == 0) r_idx++;
        }
        current_mask ^= group_mask;
    }
    for (auto &op : ops) {
        cout << op.from << " " << op.to << " " << op.amount << '\n';
    }
  /// solved by <IOIEnjoyer>
}
}
