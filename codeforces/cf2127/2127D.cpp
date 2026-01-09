#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

#include <cassert>
#include <iostream>
#include <type_traits>

template <typename S, typename T>
S power(const S begin, T base, int64_t exp) {
	S current = begin;
	while (exp) {
		if (exp & 1) current *= base;
		base *= base;
		exp >>= 1;
	}
	return current;
}

template <typename T, T modulo>
struct ModInt {
	static_assert(std::is_integral<T>::value);
	using S = ModInt<T, modulo>;
	T number;

	constexpr inline T norm(T x) {
		if (x < 0) x += modulo;
		if (x >= modulo) x -= modulo;
		return x;
	}

	ModInt() : number(0) {}
	ModInt(const T x) : number(norm(x % modulo)) {}

	constexpr T data() const { return number; }
	explicit constexpr operator T() const { return number; }
	constexpr S operator-() const {
		auto res = ModInt();
		res.number = norm(modulo - number);
		return res;
	}
	constexpr S operator~() const {
		assert(number != 0);
		return power(S(1), *this, modulo - 2);
	}

	constexpr S& operator*=(S rhs) & {
		return number = 1LL * number * rhs.number % modulo, *this;
	}
	constexpr S& operator+=(S rhs) & {
		return number = norm(number + rhs.number), *this;
	}
	constexpr S& operator-=(S rhs) & {
		return number = norm(number - rhs.number), *this;
	}
	constexpr S& operator/=(S rhs) & {
		return *this *= (~rhs);
	}

	friend constexpr S operator+(S lhs, S rhs) {
		auto res = lhs;
		return res += rhs, res;
	}
	friend constexpr S operator-(S lhs, S rhs) {
		auto res = lhs;
		return res -= rhs, res;
	}
	friend constexpr S operator*(S lhs, S rhs) {
		auto res = lhs;
		return res *= rhs, res;
	}
	friend constexpr S operator/(S lhs, S rhs) {
		auto res = lhs;
		return res /= rhs, res;
	}

	friend constexpr std::ostream& operator<<(std::ostream& out, const S& a) {
		return out << a.operator T(), out;
	}
	friend constexpr std::istream& operator>>(std::istream& in, S& a) {
		T v;
		in >> v;
		a = ModInt(v);
		return in;
	}
};

using Z = ModInt<int, 1000000007>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, M;
            std::cin >> N >> M;
            std::vector<std::pair<int, int>> edges(M);
            std::vector<int> degree(N);
            for (int i = 0; i < M; ++i) {
                int u, v;
                std::cin >> u >> v;
                --u, --v;
                if (u > v) std::swap(u, v);
                edges[i] = {u, v};
                degree[u]++, degree[v]++;
            }

            if (M != N - 1) {
                std::cout << 0 << "\n";
                return;
            }

            if (N == 2) {
                std::cout << 2 << "\n";
                return;
            }

            std::vector<int> record(N);
            for (int i = 0; i < N; ++i) {
                if (degree[i] == 1) {
                    record[i] = 1;
                }
            }

            std::vector<int> carry(N);
            degree = std::vector<int>(N);
            for (auto [u, v] : edges) {
                if (record[u] == 1) {
                    carry[v]++;
                    continue;
                }
                if (record[v] == 1) {
                    carry[u]++;
                    continue;
                }
                degree[u]++;
                degree[v]++;
            }

            if (std::find_if(degree.begin(), degree.end(), [](int x) {
                return x > 2;
            }) != degree.end()) {
                std::cout << 0 << "\n";
                std::cerr << *std::find_if(degree.begin(), degree.end(), [](int x) {
                    return x > 2;
                }) << "\n";
                return;
            }

            std::vector<Z> factor(N + 1);
            factor[0] = 1;
            for (int i = 1; i <= N; ++i) {
                factor[i] = factor[i - 1] * i;
            }
            
            Z answer = 4;
            for (int i = 0; i < N; ++i) {
                answer *= factor[carry[i]];
            }

            if (std::count(degree.begin(), degree.end(), 0) == N) {
                answer /= 2;
            }

            std::cout << answer << "\n";
        }();
    }
}