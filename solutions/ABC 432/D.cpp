/*
    Researcher: IOIEnjoyer (Algorithms & ML) — Japan
    Created: 8:31 PM (or when i acutally wrote this)
    Remark: If this compiles, it deserves a Nobel. If not… blame the optimizer.
    Note to self: don't trust sample tests.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __int128;

const int NMAX = 14;
struct Storm {
    char c;
    ll a, b;
};

struct Rect {
    ll x1, y1, x2, y2;
};

int n;
ll initial_x, initial_y;
Storm storms[NMAX + 1];
vector<Rect> rects;
int parent[1 << NMAX];

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void unite_sets(int a, int b) {
    a = find_set(a), b = find_set(b);
    if (a != b)
        parent[b] = a;
}

void print(u128 val) {
    if (val == 0) {
        cout << "0";
        return;
    }
    string s = "";
    while (val > 0) {
        s += (val % 10) + '0';
        val /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    cin >> n >> initial_x >> initial_y;
    for (int i = 1; i <= n; ++i)
        cin >> storms[i].c >> storms[i].a >> storms[i].b;
    for (int i = 0; i < (1 << n); ++i) {
        ll dx_hist[NMAX + 2] = {0}, dy_hist[NMAX + 2] = {0};

        for (int j = 1; j <= n; ++j) {
            dx_hist[j] = dx_hist[j - 1];
            dy_hist[j] = dy_hist[j - 1];
            bool is_less = !((i >> (j - 1)) & 1);
            if (storms[j].c == 'X') {
                if (is_less) dy_hist[j] -= storms[j].b;
                else dy_hist[j] += storms[j].b;
            } else {
                if (is_less) dx_hist[j] -= storms[j].b;
                else dx_hist[j] += storms[j].b;
            }
        }
        ll x0_min = 0, x0_max = initial_x - 1;
        ll y0_min = 0, y0_max = initial_y - 1;

        for (int j = 1; j <= n; ++j) {
            bool is_less = !((i >> (j - 1)) & 1);
            if (storms[j].c == 'X') {
                if (is_less) x0_max = min(x0_max, storms[j].a - dx_hist[j - 1] - 1);
                else x0_min = max(x0_min, storms[j].a - dx_hist[j - 1]);
            } else {
                if (is_less) y0_max = min(y0_max, storms[j].a - dy_hist[j - 1] - 1);
                else y0_min = max(y0_min, storms[j].a - dy_hist[j - 1]);
            }
        }
        if (x0_min <= x0_max && y0_min <= y0_max) {
            rects.push_back({x0_min + dx_hist[n], y0_min + dy_hist[n], x0_max + dx_hist[n], y0_max + dy_hist[n]});
        }
    }

    if (rects.empty()) {
        cout << "0\n\n";
        return 0;
    }
    for (size_t i = 0; i < rects.size(); ++i)
        parent[i] = i;

    for (size_t i = 0; i < rects.size(); ++i) {
        for (size_t j = i + 1; j < rects.size(); ++j) {
            Rect r1 = rects[i];
            Rect r2 = rects[j];
            bool x_touch = (r1.x2 + 1 >= r2.x1 && r2.x2 + 1 >= r1.x1);
            bool y_touch = (r1.y2 + 1 >= r2.y1 && r2.y2 + 1 >= r1.y1);
            bool x_overlap = (r1.x2 >= r2.x1 && r2.x2 >= r1.x1);
            bool y_overlap = (r1.y2 >= r2.y1 && r2.y2 >= r1.y1);

            if ((x_touch && y_overlap) || (x_overlap && y_touch)) {
                unite_sets(i, j);
            }
        }
    }
    map<int, vector<int>> components;
    for (size_t i = 0; i < rects.size(); ++i) {
        components[find_set(i)].push_back(i);
    }
    vector<u128> areas;
    for (auto const& [root, indices] : components) {
        set<ll> x_coords;
        for (int id : indices) {
            x_coords.insert(rects[id].x1);
            x_coords.insert(rects[id].x2 + 1);
        }
        vector<ll> x_vec(x_coords.begin(), x_coords.end());
        u128 total_area = 0;

        for (size_t i = 0; i + 1 < x_vec.size(); ++i) {
            ll cur_x1 = x_vec[i];
            ll cur_x2 = x_vec[i + 1];
            ll width = cur_x2 - cur_x1;
            if (width == 0) continue;

            vector<pair<ll, ll>> y_intervals;
            for (int id : indices) {
                if (rects[id].x1 <= cur_x1 && rects[id].x2 + 1 >= cur_x2) {
                    y_intervals.push_back({rects[id].y1, rects[id].y2});
                }
            }
            if (y_intervals.empty()) continue;
            sort(y_intervals.begin(), y_intervals.end());
            u128 union_len = 0;
            ll start = y_intervals[0].first;
            ll end = y_intervals[0].second;

            for (size_t k = 1; k < y_intervals.size(); ++k) {
                if (y_intervals[k].first <= end + 1) {
                    end = max(end, y_intervals[k].second);
                } else {
                    union_len += (u128)(end - start + 1);
                    start = y_intervals[k].first;
                    end = y_intervals[k].second;
                }
            }
            union_len += (u128)(end - start + 1);
            total_area += (u128)width * union_len;
        }
        areas.push_back(total_area);
    }
    sort(areas.begin(), areas.end());
    cout << areas.size() << '\n';
    for (size_t i = 0; i < areas.size(); ++i) {
        print(areas[i]);
        cout << (i == areas.size() - 1 ? "" : " ");
    }
    cout << '\n';
  /// solved by <IOIEnjoyer>
}
}
