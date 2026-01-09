#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename S, typename T>
S power(const S begin, T base, long long exp) {
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

using Z = ModInt<int, 998244353>;

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> count(N, std::vector<int>(N));
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        ++count[u][v];
        ++count[v][u];
    }

    Z answer = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            answer += Z(count[i][j]) * (count[i][j] - 1);
        }
    }

    for (int P = 2; P < N; ++P) {
        std::vector<std::vector<Z>> f(1 << P, std::vector<Z>(P + 1));
        f[0][P] = 1;
        for (int S = 0; S < 1 << P; ++S) {
            for (int i = 0; i < P + 1; ++i) {
                if (!(S | (1 << P)) & (1 << i)) continue;
                if (__builtin_popcount(S) >= 2) {
                    answer += f[S][i] * count[i][P];
                }
                for (int j = 0; j < P; ++j) {
                    if (S & (1 << j)) continue;
                    f[S ^ (1 << j)][j] += f[S][i] * count[i][j];
                }
            }
        }
    }

    std::cout << answer / 2 << std::endl;
    return 0;
}
