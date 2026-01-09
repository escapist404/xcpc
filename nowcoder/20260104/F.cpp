#include <bits/stdc++.h>

#include <cassert>
#include <iostream>
#include <type_traits>

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

const int P = 998'244'353;
using Z = ModInt<int, P>;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> d(n), u(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> d[i] >> u[i];
        --d[i];
    }

    Z ans = u[0] - d[0];
    for (int i = 0; i < n - 1; ++i) {
        int fd = std::max(d[i], d[i + 1]);
        int fu = std::min(u[i], u[i + 1]);
        int comb = std::max(fu - fd, 0);

        Z canda = (ans + u[i] - d[i]) / Z(u[i] - d[i]);
        Z candb = (ans + u[i] - d[i] - 1) / Z(u[i] - d[i]);
        ans = canda * (u[i + 1] - d[i + 1] - comb) + candb * comb;
    }

    std::cout << ans / Z(u[n - 1] - d[n - 1]) << "\n";
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
