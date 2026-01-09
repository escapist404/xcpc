#include <iostream>
#include <algorithm>
#include <vector>

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
    long long count;
    V(const int count = 0) : count(count) {}
};

V operator+ (const V& lhs, const V& rhs) {
    return V(lhs.count + rhs.count);
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            for (auto& i : A) std::cin >> i;

            SegmentTree<V> T(std::vector<V>(200001));
            long long answer = 0;
            for (int i = 0; i < N; ++i) {
                answer += T.get(std::max(A[i], A[N - 1] - A[i]) + 1, 200001).count;
                for (int j = 0; j < i; ++j) {
                    auto res = T.get(A[i] + A[j]).count;
                    T.set(A[i] + A[j], V(res + 1));
                }
            }
            std::cout << answer << "\n";
        }();
    }
}