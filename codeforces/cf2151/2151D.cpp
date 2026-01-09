#include <bits/stdc++.h>

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

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    bool ok = true;
    for (int i = n / 2 + n % 2; i < n; ++i) {
        if (a[i] > 0) {
            ok = false;
        }
    }

    if (ok == false) {
        std::cout << 0 << "\n";
        return;
    }

    if (std::accumulate(a.begin(), a.begin() + n / 2 + n % 2, 0LL) != n) {
        std::cout << 0 << "\n";
        return;
    }

    const int P = 998'244'353;
    using Z = ModInt<int, P>;

    std::vector<Z> fac(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fac[i] = fac[i - 1] * i;
    }

    auto comb = [&](int n, int m) -> Z {
        if (n > m) {
            return 0;
        }
        return fac[m] / (fac[n] * fac[m - n]);
    };

    Z ans = 1;
    int r = -(n % 2);
    for (int i = n / 2 - ((n + 1) % 2); i >= 0; --i) {
        r += 2;
        ans *= comb(a[i], r);
        r -= a[i];
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}