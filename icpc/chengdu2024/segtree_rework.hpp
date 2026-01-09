#include <type_traits>
#include <vector>

template <typename V>
constexpr auto has_addition_operator(int) -> decltype(std::declval<V>() + std::declval<V>(), bool()) {
    return true;
}

template <typename V>
constexpr auto has_addition_operator(...) {
    return false;
}

template <typename V>
class SegmentTree {
    static_assert(has_addition_operator<V>(0), "V must have operator+(V, V) defined");
    
    int n, size, log;
    std::vector<V> d;

    void update(const int x) {
        d[x] = d[x * 2] + d[x * 2 + 1];
    }

public:
    SegmentTree(const int n) : n(n) {
        assert(n > 0);
        std::tie(size, log) = [](unsigned n) {
            unsigned x = 1, c = 0;
            while (x < n) {
                x <<= 1;
                ++c;
            }
            return std::make_pair(x, c);
        }(n);
        d = std::vector<V>(2 * size);
        for (int i = size - 1; i >= 1; --i) {
            update(i);
        }
    }
    SegmentTree(const std::vector<V>& v) : n(v.size()) {
        assert(n > 0);
        std::tie(size, log) = [](unsigned n) {
            unsigned x = 1, c = 0;
            while (x < n) {
                x <<= 1;
                ++c;
            }
            return std::make_pair(x, c);
        }(n);
        d = std::vector<V>(2 * size);
        for (int i = 0; i < n; ++i) {
            d[i + size] = v[i];
        }
        for (int i = size - 1; i >= 1; --i) {
            update(i);
        }
    }

    void set(const int p, const V& x) {
        d[p + size] = x;
        for (int i = 1, q = p + size; i <= log; ++i) {
            update(q >> i);
        }
    }

    V get(const int p) const {
        return d[p + size];
    }

    V get(const int l, const int r) const {
		V L = V(), R = V();
		int dl = l + size, dr = r + size;
		while (dl < dr) {
			if (dl & 1) L = L + D[dl++];
			if (dr & 1) R = D[--dr] + R;
			dl >>= 1, dr >>= 1;
		}
		return L + R;
	}

    V get_all() const {
        return d[1];
    }

    template <typename P>
    int max_right(const int l, P& pred) const {
        if (l == n) {
            return n;
        }
        int dl = l + size;
        V c();
        do {
            while ((dl & 1) == false) {
                dl >>= 1;
            }
            if (!pred(c + d[dl])) {
                while (dl < size) {
                    dl <<= 1;
                    if (pred(c + d[dl])) {
                        c = c + d[dl];
                        ++dl;
                    }
                }
                return dl - size;
            }
            c = op(c, d[dl]);
            ++dl;
        } while ((dl & -dl) != dl);
        return n;
    }
};