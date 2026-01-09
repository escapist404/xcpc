#include <bits/stdc++.h>

using i64 = long long;

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename V>
constexpr auto has_addition_operator(int) -> decltype(std::declval<V>() + std::declval<V>(), bool()) {
	return true;
}

template <typename V>
constexpr bool has_addition_operator(...) {
	return false;
}

template <typename V>
class SegmentTree {
	static_assert(has_addition_operator<V>(0),
				  "V must have operator+(V, V) defined");

	int N, size, log;
	std::vector<V> D;

	constexpr void update(const int x) {
		D[x] = D[x * 2] + D[x * 2 + 1];
	}

public:
	SegmentTree(const std::vector<V>& v) : N(int(v.size())) {
		assert(v.size() > 0);
		size = [](unsigned int n) {
			unsigned int x = 1;
			while (x < n) x <<= 1;
			return x;
		}(N);
		log = __builtin_ctz(size);
		D = std::vector<V>(2 * size);
		for (int i = 0; i < N; i++) D[size + i] = v[i];
		for (int i = size - 1; i >= 1; i--) D[i] = D[i * 2] + D[i * 2 + 1];
	}

	inline constexpr void set(int p, V x) {
		p += size, D[p] = x;
		for (int i = 1; i <= log; i++) update(p >> i);
	}

	inline constexpr V get(const int p) const {
		return D[p + size];
	}

	inline constexpr V get(int l, int r) const {
		V L = V(), R = V();
		l += size, r += size;
		while (l < r) {
			if (l & 1) L = L + D[l++];
			if (r & 1) R = D[--r] + R;
			l >>= 1, r >>= 1;
		}
		return L + R;
	}
	inline constexpr V get() const { return D[1]; }

    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= N && f(V()));
        if (l == N) return N;
        l += size;
        V S = V();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(S + D[l])) {
                while (l < size) {
                    l = (2 * l);
                    if (f(S + D[l])) {
                        S = S + D[l];
                        l++;
                    }
                }
                return l - size;
            }
            S = S + D[l];
            l++;
        } while ((l & -l) != l);
        return N;
    }

    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= N && f(V()));
        if (r == 0) return 0;
        r += size;
        V S = V();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(D[r] + S)) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(D[r] + S)) {
                        S = D[r] + S;
                        r--;
                    }
                }
                return r + 1 - size;
            }
            S = D[r] + S;
        } while ((r & -r) != r);
        return 0;
    }
};

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);  
}

struct V {
    int v;
    V() : v(0) {}
    V(const int v) : v(v) {}
    friend V operator+(const V& x, const V& y) {
        return V(gcd(x.v, y.v));
    }
};

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<V> init(n - 1);
    for (int i = 1; i < n; ++i) {
        init[i - 1].v = a[i - 1] > a[i] ? i : 0;
    }

    SegmentTree<V> T(init);
    for (int i = 0; i < q; ++i) {
        int p, v;
        std::cin >> p >> v;
        --p;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
