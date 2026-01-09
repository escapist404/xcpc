#include <cassert>
#include <iostream>
#include <type_traits>
#include <iostream>
#include <vector>
#include <algorithm>


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
// using Z = double;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, Z>>> C(m + 1);
    std::vector<Z> f(m + 1), s(m + 2, 1);
    f[0] = 1;
    
    for (int i = 0; i < n; ++i) {
        int l, r;
        Z p, q;
        std::cin >> l >> r >> p >> q;
        C[r].emplace_back(l, p / q);
        s[r] *= 1 - p / q;
    }

    for (int i = 1; i <= m; ++i) {
        s[i] *= s[i - 1];
    }

    for (int i = 1; i <= m; ++i) {
        for (auto [last, p] : C[i]) {
            f[i] += f[last - 1] * (p / (1 - p)) * (s[i] / s[last - 1]);
        }
    }

    std::cout << f[m] << "\n";
    return 0;
}
