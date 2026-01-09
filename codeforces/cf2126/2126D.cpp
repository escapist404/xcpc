#include <vector>
#include <iostream>
#include <algorithm>

template <typename V>
class SegmentTree {
	int N, size, log;
	std::vector<V> D;

	constexpr void update(const int x) {
		D[x] = D[x * 2] + D[x * 2 + 1];
	}

public:
    SegmentTree(const std::vector<V>& v) : N(int(v.size())) {
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
};

struct V {
    bool value;
    V(const bool value = false) : value(value) {}
};

V operator + (const V L, const V R) {
    return V(L.value | R.value);
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, k;
            std::cin >> n >> k;
            std::vector<std::tuple<int, int, int>> casino(n);
            std::vector<int> ref = {k};
            for (auto& [l, r, real] : casino) {
                std::cin >> l >> r >> real;
                ref.push_back(l);
                ref.push_back(r);
                ref.push_back(real);
            }
            std::sort(ref.begin(), ref.end());
            ref.erase(std::unique(ref.begin(), ref.end()), ref.end());

            k = std::lower_bound(ref.begin(), ref.end(), k) - ref.begin();
            for (auto& [l, r, real] : casino) {
                l = std::lower_bound(ref.begin(), ref.end(), l) - ref.begin();
                r = std::lower_bound(ref.begin(), ref.end(), r) - ref.begin();
                real = std::lower_bound(ref.begin(), ref.end(), real) - ref.begin();
            }

            std::sort(casino.begin(), casino.end(), [](std::tuple<int, int, int> x, std::tuple<int, int, int> y)    {
                return std::get<2>(x) < std::get<2>(y);
            });

            SegmentTree<V> T(std::vector<V>(ref.size()));
            T.set(k, V(true));

            for (auto [l, r, real] : casino) {
                auto result = T.get(l, r + 1);
                auto current = T.get(real);
                if (current.value == false) T.set(real, result);
            }

            for (int i = (int)ref.size() - 1; i >= 0; --i) {
                if (T.get(i).value == true) {
                    std::cout << ref[i] << "\n";
                    break;
                }
            }
        }();
    }
}