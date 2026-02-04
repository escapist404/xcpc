#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

const int P = 998244353;

constexpr int power(int base, int exp) {
    int ret = 1;
    while (exp) {
        if (exp & 1) {
            ret = 1LL * ret * base % P;
        }
        base = 1LL * base * base % P;
        exp >>= 1;
    }
    return ret;
}

constexpr int inv(int base) {
    return power(base, P - 2);
}

struct Sequence {
    int n;
    std::vector<int> father;
    int get(int x) {
        return father[x] == x ? x : father[x] = get(father[x]);
    }
    bool connected(int x, int y) {
        return get(x) == get(y);
    }
    void merge(int x, int y) {
        if (connected(x, y)) {
            return;
        }
        x = get(x);
        y = get(y);
        father[std::min(x, y)] = std::max(x, y);
    }
    int erase(int l, int r) {
        int p = l, a = 0;
        while (p < r) {
            int t = get(p) + 1;
            if (p + 1 == t) {
                a++;
                merge(p, t);
            }
            p = get(p);
        }
        return a;
    }
    Sequence(int n) : n(n), father(n) {
        std::iota(father.begin(), father.end(), 0);
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }

    std::vector<int> ifac(n + 1);
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i) {
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % P;
    }

    auto perm = [&](int all, int choose) {
        return choose <= all ? (1LL * fac[all] * ifac[all - choose] % P) : 0LL;
    };

    std::vector<std::vector<std::pair<int, int>>> seg(n);
    std::vector<int> u(n, -1), v(n, n + 1);
    for (int i = 0; i < m; ++i) {
        int l, r, k;
        std::cin >> l >> r >> k;
        --l, --k;
        u[k] = std::max(u[k], l);
        v[k] = std::min(v[k], r);
        seg[k].emplace_back(l, r);
    }

    int lst = 0, ans = 1;
    Sequence S(n + 1);
    for (int i = 0; i < n; ++i) {
        if (u[i] >= v[i]) {
            ans = 0;
        }
        if (ans == 0) {
            break;
        }
        if (u[i] == -1 && v[i] == n + 1) {
            lst++;
            continue;
        }
        int tar = S.erase(u[i], v[i]);
        int emp = 0;
        for (auto [l, r] : seg[i]) {
            emp += S.erase(l, r);
        }
        ans = 1LL * ans * perm(lst, tar - 1) % P * tar % P;
        ans = 1LL * ans * perm(lst - tar + 1, emp) % P;
        lst -= emp + tar - 1;
    }

    ans = 1LL * ans * perm(lst, S.erase(0, n)) % P;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
