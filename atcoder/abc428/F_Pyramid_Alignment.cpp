#include <bits/stdc++.h>

#include <cassert>
#include <vector>

template <typename Value, typename Lazy>
class LazySegmentTree {
	int n;
	std::vector<Value> value;
	std::vector<Lazy> lazy;

	constexpr inline int ls(const int x) { return x * 2 + 1; }
	constexpr inline int rs(const int x) { return x * 2 + 2; }

	constexpr void push_down(const int x) {
		value[ls(x)] += lazy[x], value[rs(x)] += lazy[x];
		lazy[ls(x)] += lazy[x], lazy[rs(x)] += lazy[x];
		lazy[x] = Lazy();
	}

	void set(const int x, const int l, const int r, const int L, const int R, const Lazy& K) {
		if (L <= l && r <= R) return value[x] += K, lazy[x] += K, void();
		int m = (l + r) / 2;
		push_down(x);
		if (L < m) set(ls(x), l, m, L, R, K);
		if (R > m) set(rs(x), m, r, L, R, K);
		value[x] = value[ls(x)] + value[rs(x)];
	}
	Value get(const int x, const int l, const int r, const int L, const int R) {
		if (L <= l && r <= R) return value[x];
		int m = (l + r) / 2;
		push_down(x);
		if (R <= m) return get(ls(x), l, m, L, R);
		if (L >= m) return get(rs(x), m, r, L, R);
		return get(ls(x), l, m, L, R) + get(rs(x), m, r, L, R);
	}

public:
	void set(const int l, const int r, const Lazy& k) { set(0, 0, n, l, r, k); }
	void set(const int p, const Lazy& k) { set(p, p + 1, k); }
	void set(const Lazy& k) { value[0] += k, lazy[0] += k; }
	Value get(const int l, const int r) { return get(0, 0, n, l, r); }
	Value get(const int p) { return get(p, p + 1); }
	Value get() { return value[0]; }

	LazySegmentTree(const int n)
		: n(n), value(n * 4), lazy(n * 4) {
		std::vector<Value> init(n, Value());
		auto build = [&](auto self, const int x, const int l, const int r) {
			if (l + 1 == r) return value[x] = init[l], void();
			int m = (l + r) / 2;
			self(self, this->ls(x), l, m), self(self, this->rs(x), m, r);
			value[x] = value[this->ls(x)] + value[this->rs(x)];
		};
		build(build, 0, 0, n);
	}
	LazySegmentTree(const int n, std::vector<Value> init)
		: n(n), value(n * 4), lazy(n * 4) {
		assert(init.size() == n);
		auto build = [&](auto self, const int x, const int l, const int r) {
			if (l + 1 == r) return value[x] = init[l], void();
			int m = (l + r) / 2;
			self(self, this->ls(x), l, m), self(self, this->rs(x), m, r);
			value[x] = value[this->ls(x)] + value[this->rs(x)];
		};
		build(build, 0, 0, n);
	}
};

struct L {
    char exist;
    int op;
    L(const char exist = 0, const int op = 0) : exist(exist), op(op) {}
    L& operator+=(const L& x) {
        if (x.exist != 0) {
            exist = x.exist;
            op = x.op;
        }
        return *this;
    }
};

struct V {
    std::pair<int, int> seg;
    V(const std::pair<int, int>& seg = {0, 0}) : seg(seg) {}
    V& operator+=(const L& x) {
        if (x.exist != 0) {
            if (x.exist == 'R') {
                seg.first = x.op - (seg.second - seg.first);
                seg.second = x.op;
            } else if (x.exist == 'L') {
                seg.second = x.op + seg.second - seg.first;
                seg.first = x.op;
            }
        }
        return *this;
    }
    friend V operator+(const V& lhs, const V& rhs) {
        return rhs;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    std::vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> w[i];
    }

    std::vector<V> init(n);
    for (int i = 0; i < n; ++i) {
        init[i].seg = {0, w[i]};
    }

    LazySegmentTree<V, L> T(n, init);

    int q;
    std::cin >> q;
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int v;
            std::cin >> v;
            --v;
            int pos = T.get(v).seg.first;
            T.set(0, v + 1, L{'L', pos});
        } else if (type == 2) {
            int v;
            std::cin >> v;
            --v;
            int pos = T.get(v).seg.second;
            T.set(0, v + 1, L{'R', pos});
        } else {
            int x;
            std::cin >> x;
            int l = 0, r = n + 1;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                auto y = T.get(0, m).seg;
                if (y.first <= x && y.second > x) {
                    r = m;
                } else {
                    l = m;
                }
            }
            std::cout << n - l << "\n";
        }
        // std::cerr << "::::::::\n";
        // for (int j = 0; j < n; ++j) {
        //     auto x = T.get(j);
        //     std::cerr << x.seg.first << " " << x.seg.second << "\n";
        // }
    }
}