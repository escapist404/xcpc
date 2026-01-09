#include <bits/stdc++.h>

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

template <typename T>
class ODT {
private:
    std::map<int, T> map;
 
public:
    ODT(const std::vector<T> arr) {
        for (int i = 0; i < (int)arr.size(); ++i) {
            map[i] = arr[i];
        }
        map[arr.size()] = T();
    }
    inline auto split(int pos) {
        auto item = map.lower_bound(pos);
        if (item->first == pos) return item;
        --item;
        map.insert({pos, item->second});
        return ++item;
    }
    void set(const int l, const int r, const T v) {
        auto end = split(r);
        map.erase(split(l), end);
        map[l] = v;
    }
    T get(const int pos) {
        auto item = --map.upper_bound(pos);
        return item->second;
    }
};

struct V {
    int v;
    V(const int v = 0) : v(v) {}
    V operator+(const V& x) {
        return V(v + x.v);
    }
};

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }

    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
        --b[i];
    }

    std::multiset<int> l;
    for (int i = 0; i < k; ++i) {
        int x;
        std::cin >> x;
        l.insert(x);
    }

    bool ok = [&]() {
        int pos = 0;
        for (int i = 0; i < n; ++i) {
            if (pos < m && b[pos] == a[i]) {
                ++pos;
            }
        }
        return pos == m;
    }();

    if (ok == false) {
        std::cout << "NO\n";
        return;
    }

    std::vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        r[a[i]] = i;
    }

    std::vector<int> v(n);
    for (int i = 0; i < m; ++i) {
        v[b[i]] = 1;
    }

    SegmentTree<V> S(std::vector<V>(n, 1));
    ODT<std::pair<int, int>> T(std::vector<std::pair<int, int>>(n, {0, n}));

    for (int i = n - 1; i >= 0; --i) {
        if (v[i] == 0) {
            auto [lb, rb] = T.get(r[i]);
            auto it = l.upper_bound(S.get(lb, rb).v);
            if (it != l.begin()) {
                --it;
            } else {
                std::cout << "NO\n";
                return;
            }
            l.erase(it);
            S.set(r[i], V{0});
        } else {
            auto [lb, rb] = T.get(r[i]);
            if (r[i] > lb) {
                T.set(lb, r[i], {lb, r[i]});
            }
            if (r[i] + 1 < rb) {
                T.set(r[i] + 1, rb, {r[i] + 1, rb});
            }
            T.set(r[i], r[i] + 1, {r[i], r[i] + 1});
        }
    }

    std::cout << "YES\n";
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
