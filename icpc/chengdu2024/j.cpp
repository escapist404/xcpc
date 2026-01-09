#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;

    int active = -1, cur_score = 0;
    std::vector<i64> score(m);
    std::set<int> done;

    while (q--) {
        int type;
        std::cin >> type;

        if (type == 1) {
            std::cin >> active;
            active--;
            cur_score = m;
            done.clear();
        } else if (type == 2) {
            int id, x;
            std::cin >> id >> x;
            --id, --x;
            if (x == active && done.count(id) == 0) {
                score[id] += cur_score--;
                done.insert(id);
            }
        } else {
            int id, x;
            std::cin >> id >> x;
            --id, --x;
            if (x == active && done.count(id) == 0) {
                done.insert(id);
            }
        }
    }

    std::vector<std::pair<int, i64>> rank(m);
    for (int i = 0; i < m; ++i) {
        rank[i] = {i + 1, score[i]};
    }

    std::sort(rank.begin(), rank.end(), [](auto x, auto y) {
        if (x.second != y.second) {
            return x.second > y.second;
        }
        return x.first < y.first;
    });

    for (auto [id, sc] : rank) {
        std::cout << id << " " << sc << "\n";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
