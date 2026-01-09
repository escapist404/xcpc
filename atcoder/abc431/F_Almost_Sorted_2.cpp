#include <bits/stdc++.h>

using i64 = long long;

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

const int P = 998244353;
using Z = ModInt<int, P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, D;
    std::cin >> N >> D;

    std::vector<Z> fac(N + 1);
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fac[i] = fac[i - 1] * i;
    }
    
    std::vector<Z> ifac(N + 1);
    ifac[N] = ~fac[N];
    for (int i = N - 1; i >= 0; --i) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }

    auto comb = [&](int u, int d) -> Z {
        return u >= d ? fac[u] * ifac[d] * ifac[u - d] : Z(0);
    };

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    int V = *std::max_element(A.begin(), A.end());
    std::vector<int> c(V + 1);

    for (int i = 0; i < N; ++i) {
        c[A[i]]++;
    }

    std::vector<int> pc(V + 2);
    for (int i = 1; i <= V + 1; ++i) {
        pc[i] = pc[i - 1] + c[i - 1];
    }

    Z ans = 1;
    for (int i = 1; i <= V; ++i) {
        ans *= comb(pc[i + 1] - pc[std::max(i - D, 0)], c[i]);
    }

    std::cout << ans << "\n";

    return 0;
}