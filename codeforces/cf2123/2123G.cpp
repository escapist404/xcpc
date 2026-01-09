#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

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

template<int C>
struct V {
    std::vector<int> lhs, rhs, count;
    V(const std::vector<int> left = std::vector<int>(C), const std::vector<int> right = std::vector<int>(C), const std::vector<int> count = std::vector<int>(C))
        : lhs(left), rhs(right), count(count) {}
};

template<int C>
V<C> operator+(const V<C>& L, const V<C>& R) {
    V<C> result(L.lhs, R.rhs, std::vector<int>(C));
    for (int i = 0; i < C; ++i) {
        result.count[i] = L.count[i] + R.count[i] - (L.rhs[i] == R.lhs[i]);
    }
    return result;
}

const int C = 64;

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, M, Q;
            std::cin >> N >> M >> Q;
            std::vector<int> A(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> A[i];
            }

            std::vector<int> factor;
            for (int i = 1; i * i <= M; ++i) {
                if (M % i == 0) {
                    factor.push_back(i);
                    int res = M / i;
                    if (res != i) {
                        factor.push_back(res);
                    }
                }
            }

            std::sort(factor.begin(), factor.end());
            std::vector<V<C>> P(N);

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < (int)factor.size(); ++j) {
                    P[i].lhs[j] = P[i].rhs[j] = A[i] % factor[j];
                    P[i].count[j] = 1;
                }
            }

            SegmentTree<V<C>> T(P);

            for (int i = 0; i < Q; ++i) {
                int type;
                std::cin >> type;
                if (type == 2) {
                    int k;
                    std::cin >> k;
                    int g = std::gcd(k, M);
                    int r = std::lower_bound(factor.begin(), factor.end(), g) - factor.begin();
                    if (T.get().count[r] <= g) {
                        std::cout << "YES\n";
                    } else {
                        std::cout << "NO\n";
                    }
                    std::cerr << T.get().count[r] << "\n";
                } else {
                    int c, x;
                    std::cin >> c >> x;
                    --c;
                    V<C> res;
                    for (int j = 0; j < (int)factor.size(); ++j) {
                        res.lhs[j] = res.rhs[j] = x % factor[j];
                        res.count[j] = 1;
                    }
                    T.set(c, res);
                }
            }
        }();
    }
}