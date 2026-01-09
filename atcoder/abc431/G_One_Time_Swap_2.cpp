#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
struct Fenwick {
    static_assert(std::is_integral<T>::value);
    size_t n;
    std::vector<T> d;
    
private:
    T sum(size_t p) {
        T r = 0;
        while (p > 0) {
            r += d[p];
            p -= p & (-p);
        }
        return r;
    }

public:
    Fenwick(size_t n) : n(n), d(n + 1) {}
    
    void add(size_t p, T x) {
        p++;
        while (p <= n) {
            d[p] += x;
            p += p & (-p);
        }
    }
    
    T sum(size_t l, size_t r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }
    
    std::vector<std::tuple<int, i64, int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        auto& [id, k, l, r] = queries[i];
        id = i;
        std::cin >> k;
        --k;
    }
    
    std::sort(queries.begin(), queries.end(), [](auto x, auto y) {
        return std::get<1>(x) < std::get<1>(y);
    });
    
    Fenwick<int> P(n);
    
    std::vector<int> c(n), d(n);
    for (int i = n - 1; i >= 0; --i) {
        c[i] = P.sum(0, a[i]);
        d[i] = P.sum(a[i] + 1, n);
        P.add(a[i], 1);
    }
    
    i64 sumd = std::accumulate(d.begin(), d.end(), 0LL);
    
    std::vector<std::vector<int>> f(n), g(n);
    for (int i = n - 1; i >= 0; --i) {
        f[a[i]].push_back(i);
    }
    
    int eql = -1, eqr = -1;
    for (int i = 0; i < n; ++i) {
        if (f[i].size() >= 2) {
            eql = f[i][1];
            eqr = f[i][0];
            break;
        }
    }
    
    int now = 0;
    i64 pc = 0;
    for (int i = 0; i < n; ++i) {
        while (now < q) {
            auto& [id, k, l, r] = queries[now];
            if (k >= pc + c[i]) {
                break;
            }

            int k1 = k - pc;
            int vl = 0, vr = a[i];
            while (vl + 1 < vr) {
                int vm = (vl + vr) / 2;
                int ret = P.sum(0, vm);
                if (ret <= k1) {
                    vl = vm;
                } else {
                    vr = vm;
                }
            }
            
            l = i;
            r = f[vl][k1 - P.sum(0, vl)];
            ++now;
        }
        
        pc += c[i];
        P.add(a[i], -1);
        f[a[i]].pop_back();
    }
    
    while (now < q) {
        auto& [id, k, l, r] = queries[now];
        if (k >= 1LL * n * (n - 1) / 2 - sumd) {
            break;
        }
        
        l = eql;
        r = eqr;
        ++now;
    }
    
    i64 sd = 1LL * n * (n - 1) / 2 - sumd;
    for (int i = n - 1; i >= 0; --i) {
        int offset = P.sum(0, a[i] + 1);
        while (now < q) {
            auto& [id, k, l, r] = queries[now];
            if (k >= sd + d[i]) {
                break;
            }
            
            i64 k1 = k - sd;
            int vl = a[i] + 1, vr = n;
            while (vl + 1 < vr) {
                int vm = (vl + vr) / 2;
                int ret = P.sum(0, vm) - offset;
                if (ret <= k1) {
                    vl = vm;
                } else {
                    vr = vm;
                }
            }
            
            l = i;
            r = g[vl][(int)g[vl].size() - 1 - k1 + P.sum(0, vl) - offset];
            ++now;
        }

        sd += d[i];
        P.add(a[i], 1);
        g[a[i]].push_back(i);
    }
    
    std::sort(queries.begin(), queries.end());
    for (auto [id, k, l, r] : queries) {
        std::cout << l + 1 << " " << r + 1 << "\n";
    }
    
    return 0;
}
