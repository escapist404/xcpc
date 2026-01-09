#include <bits/stdc++.h>

const int P = 998'244'353;

template <typename V, typename T>
class LazySegmentTree {
    int n;
    std::vector<V> val;
    std::vector<T> tag;
 
    constexpr int ls(const int id) const {
        return (id << 1) | 1;
    }
    constexpr int rs(const int id) const {
        return (id + 1) << 1;
    }
 
    void push(const int id) {
        val[ls(id)] += tag[id];
        val[rs(id)] += tag[id];
        tag[ls(id)] += tag[id];
        tag[rs(id)] += tag[id];
        tag[id] = T();
    }
 
    void pull(const int id) {
        val[id] = val[ls(id)] + val[rs(id)];
    }
 
    V get(const int l, const int r, const int id, const int cl, const int cr) {
        if (l <= cl && cr <= r) {
            return val[id];
        }
        push(id);
        int cm = (cl + cr) >> 1;
        if (r <= cm) {
            return get(l, r, ls(id), cl, cm);
        }
        if (l >= cm) {
            return get(l, r, rs(id), cm, cr);
        }
        return get(l, r, ls(id), cl, cm) + get(l, r, rs(id), cm, cr);
    }
 
    void set(const T& t, const int l, const int r, const int id, const int cl, const int cr) {
        if (l <= cl && cr <= r) {
            val[id] += t;
            tag[id] += t;
            return;
        }
        push(id);
        int cm = (cl + cr) >> 1;
        if (l < cm) {
            set(t, l, r, ls(id), cl, cm);
        }
        if (r > cm) {
            set(t, l, r, rs(id), cm, cr);
        }
        pull(id);
    }
 
public:
    V get(const int l, const int r) {
        if (r - l >= 1) {
            return get(l, r, 0, 0, n);
        } else {
            return V();
        }
    }
    void set(const T& t, const int l, const int r) {
        if (r - l >= 1) {
            set(t, l, r, 0, 0, n);
        }
    }
 
    LazySegmentTree(const std::vector<V>& v) : n(v.size()), val(n << 2), tag(n << 2) {
        auto build = [&](auto& self, const int id, const int cl, const int cr) {
            if (cr - cl == 1) {
                val[id] = v[cl];
                return;
            }
            int cm = (cl + cr) >> 1;
            self(self, ls(id), cl, cm);
            self(self, rs(id), cm, cr);
            pull(id);
        };
        build(build, 0, 0, n);
    }
};

struct Tag {
    int mul, add;
    Tag(const int mul = 1, const int add = 0) : mul(mul), add(add) {}
    Tag& operator+=(const Tag& y) {
        return *this = Tag(1LL * y.mul * mul % P, (1LL * y.mul * add % P + y.add) % P);
    }
};
 
struct Value {
    int sum;
    Value(const int sum = 0) : sum(sum) {}
    Value& operator+=(const Tag& y) {
        return *this = Value((1LL * y.mul * sum % P + y.add) % P);
    }
    
    Value operator+(const Value& y) {
        return Value((sum + y.sum) % P);
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> view_l = {0}, view_r = {0};
    for (int i = 0; i < n; ++i) {
        if (view_l.back() < a[i]) {
            view_l.push_back(a[i]);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (view_r.back() < a[i]) {
            view_r.push_back(a[i]);
        }
    }

    LazySegmentTree<Value, Tag> sub_l(std::vector<Value>(view_l.size()));
    LazySegmentTree<Value, Tag> sub_r(std::vector<Value>(view_r.size()));
    std::vector<int> comb_l(n), comb_r(n);

    sub_l.set({1, 1}, 0, 1);
    sub_r.set({1, 1}, 0, 1);

    for (int i = 0; i < n; ++i) {
        int id = std::lower_bound(view_l.begin(), view_l.end(), a[i]) - view_l.begin();
        sub_l.set({2, 0}, id, (int)view_l.size());

        if (view_l[id] == a[i]) {
            auto last = sub_l.get(id - 1, id).sum;
            sub_l.set({1, last}, id, id + 1);
        }

        if (view_l.back() == a[i]) {
            comb_l[i] = sub_l.get((int)view_l.size() - 2, (int)view_l.size() - 1).sum;
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int id = std::lower_bound(view_r.begin(), view_r.end(), a[i]) - view_r.begin();
        sub_r.set({2, 0}, id, (int)view_r.size());

        if (view_r[id] == a[i]) {
            auto last = sub_r.get(id - 1, id).sum;
            sub_r.set({1, last}, id, id + 1);
        }

        if (view_r.back() == a[i]) {
            comb_r[i] = sub_r.get((int)view_r.size() - 2, (int)view_r.size() - 1).sum;
        }
    }

    int ans = 0;
    for (int i = 0, con = 0; i < n; ++i) {
        (ans += 1LL * (con + comb_l[i]) % P * comb_r[i] % P) %= P;
        (con += (con + comb_l[i]) % P) %= P;
    }

    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
