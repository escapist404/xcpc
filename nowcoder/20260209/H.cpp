#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

template <typename T>
struct SegmentTree {
    int n;
    std::vector<T> info;

    void set(int id, int l, int r, int p, const T& x) {
        if (r - l == 1) {
            info[id] = x;
            return;
        }
        if (p < (l + r) / 2) {
            set(2 * id + 1, l, (l + r) / 2, p, x);
        } else {
            set(2 * id + 2, (l + r) / 2, r, p, x);
        }
        info[id] = info[2 * id + 1] + info[2 * id + 2];
    }

    T get(int id, int l, int r, int L, int R) const {
        if (L <= l && r <= R) {
            return info[id];
        }
        if ((l + r) / 2 >= R) {
            return get(2 * id + 1, l, (l + r) / 2, L, R);
        }
        if ((l + r) / 2 <= L) {
            return get(2 * id + 2, (l + r) / 2, r, L, R);
        }
        return get(2 * id + 1, l, (l + r) / 2, L, R) + get(2 * id + 2, (l + r) / 2, r, L, R);
    }

    SegmentTree(const int n) : n(n), info(4 * n) {
        auto build = [&](auto& self, int id, int l, int r) {
            if (l + 1 == r) {
                info[id] = T();
                return;
            }
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            info[id] = info[2 * id + 1] + info[2 * id + 2];
        };
        build(build, 0, 0, n);
    }

    SegmentTree(const std::vector<T>& v) : n(v.size()), info(4 * n) {
        auto build = [&](auto& self, int id, int l, int r) {
            if (l + 1 == r) {
                info[id] = v[l];
                return;
            }
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            info[id] = info[2 * id + 1] + info[2 * id + 2];
        };
        build(build, 0, 0, n);
    }
};

using i64 = long long;

struct V {
    int id;
    i64 max;
    V() : id(-1), max(0) {}
    V(int id, i64 max) : id(id), max(max) {}
};

V operator+(const V& l, const V& r) {
    return l.max > r.max ? l : r;
}

const int dx[] = {2, 1, 0, -1, -2, -1, 0, 1, 1, 0, -1, 0, 0};
const int dy[] = {0, 1, 2, 1, 0, -1, -2, -1, 0, 1, 0, -1, 0};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> a(n * m);
    for (int i = 0; i < n * m; ++i) {
        std::cin >> a[i];
    }

    std::vector<V> v(n * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            v[i * m + j].id = i * m + j;
            i64 c = 0;
            for (int k = 0; k < 15; ++k) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) {
                    continue;
                }
                int nd = ni * m + nj;
                c += a[nd];
            }
            v[i * m + j].max = c;
        }
    }

    SegmentTree<V> T(v);
    while (q--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        --x, --y;
        int i = x * m + y;
        for (int k = 0; k < 15; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            int ni = nx * m + ny;
            T.set(0, 0, n * m, ni, V(ni, T.get(0, 0, n * m, ni, ni + 1).max + z));
        }
        int best = T.get(0, 0, n * m, 0, n * m).id;
        std::cout << best / m + 1 << " " << best % m + 1 << "\n";
    }

    return 0;
}
