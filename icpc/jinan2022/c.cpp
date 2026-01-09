#include <bits/stdc++.h>

template <typename T>
T power(const T& unit, T base, long long exp) {
    auto result = unit;
    while (exp) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

template <typename T, T _mod>
struct ModInt {
    T value;
    ModInt(const long long value = 0) : value(value % _mod) {
        norm();
    }
    void norm() {
        if (value >= _mod) {
            value -= _mod;
        }
        if (value < 0) {
            value += _mod;
        }
    }
    ModInt<T, _mod> operator~() const {
        if (value == 0) {
            throw std::runtime_error("attempt to divide by zero");
        }
        return power(ModInt<T, _mod>(1), *this, _mod - 2);
    }
    ModInt<T, _mod>& operator+=(const ModInt<T, _mod>& x) {
        value += x.value;
        norm();
        return *this;
    }
    ModInt<T, _mod>& operator-=(const ModInt<T, _mod>& x) {
        value -= x.value;
        norm();
        return *this;
    }
    ModInt<T, _mod>& operator*=(const ModInt<T, _mod>& x) {
        value = 1LL * value * x.value % _mod;
        return *this;
    }
    ModInt<T, _mod>& operator/=(const ModInt<T, _mod>& x) {
        return *this *= (~x);
    }
    friend std::istream& operator>>(std::istream& is, ModInt<T, _mod>& x) {
        long long v;
        is >> v;
        x.value = v % _mod;
        x.norm();
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const ModInt<T, _mod>& x) {
        os << x.value;
        return os;
    }
    friend ModInt<T, _mod> operator+(const ModInt<T, _mod>& x, const ModInt<T, _mod>& y) {
        auto res = x;
        res += y;
        return res;
    }
    friend ModInt<T, _mod> operator-(const ModInt<T, _mod>& x, const ModInt<T, _mod>& y) {
        auto res = x;
        res -= y;
        return res;
    }
    friend ModInt<T, _mod> operator*(const ModInt<T, _mod>& x, const ModInt<T, _mod>& y) {
        auto res = x;
        res *= y;
        return res;
    }
    friend ModInt<T, _mod> operator/(const ModInt<T, _mod>& x, const ModInt<T, _mod>& y) {
        auto res = x;
        res /= y;
        return res;
    }
};

const int P = 998'244'353;
using Z = ModInt<int, P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;

        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<Z> fac(n + 1), ifac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = fac[i - 1] * i;
    }
    ifac[n] = ~fac[n];
    for (int i = n - 1; i >= 0; --i) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }

    std::vector<Z> down(n, 1);
    std::vector<std::vector<std::vector<Z>>> choose(n);
    std::vector<std::vector<Z>> up(n, std::vector<Z>(n, 0));
    std::vector<std::vector<Z>> ans(n, std::vector<Z>(n, 0));

    up[0][0] = 1;

    std::vector<int> size(n, 1);
    auto init = [&](auto& self, int u, int p) -> void {
        auto it = std::find(adj[u].begin(), adj[u].end(), p);
        if (it != adj[u].end()) {
            adj[u].erase(it);
        }

        int deg = adj[u].size();
        down[u] *= fac[deg];

        for (auto v : adj[u]) {
            self(self, v, u);
            size[u] += size[v];
            down[u] *= down[v];
        }

        choose[u].resize(deg + 1, std::vector<Z>(size[u]));

        choose[u][0][0] = 1;
        for (int i = 0; i < deg; ++i) {
            int v = adj[u][i];
            for (int j = deg; j >= 1; --j) {
                for (int k = size[u] - 1; k >= size[v]; --k) {
                    choose[u][j][k] += choose[u][j - 1][k - size[v]];
                }
            }
        }
    };

    auto get = [&](auto& self, const int u) -> void {
        int deg = adj[u].size();
        for (int i = 0; i < deg; ++i) {
            int v = adj[u][i];

            for (int j = 1; j <= deg; ++j) {
                for (int k = size[v]; k < size[u]; ++k) {
                    choose[u][j][k] -= choose[u][j - 1][k - size[v]];
                }
            }

            Z res = down[u] / down[v] * ifac[deg];
            std::vector<Z> between(size[u] + 1);
            for (int k = 1; k <= size[u]; ++k) {
                for (int before = 0; before < deg; ++before) {
                    int after = deg - before - 1;
                    between[k] += choose[u][before][k - 1] * fac[before] * fac[after];
                }
                between[k] *= res;
            }

            for (int j = 0; j < n; ++j) {
                for (int k = 1; k <= size[u] && j + k < n; ++k) {
                    up[v][j + k] += up[u][j] * between[k];
                }
            }

            for (int j = deg; j >= 1; --j) {
                for (int k = size[u] - 1; k >= size[v]; --k) {
                    choose[u][j][k] += choose[u][j - 1][k - size[v]];
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            ans[u][i] = up[u][i] * down[u];
        }

        for (auto v : adj[u]) {
            self(self, v);
        }
    };

    init(init, 0, -1);
    get(get, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << ans[i][j] << " \n"[j == n - 1];
        }
    }

    return 0;
}
