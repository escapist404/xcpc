#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <numeric>
#include <cassert>

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
    // f_C = \sum (A_i / S) f_i (A_i greater) + \sum (A_i / S) f_C (A_i smaller) + 1
    // (S - prefix) / S * f_C = \sum (A_i / S) f_i (A_i greater) + 1

    int N, C;
    std::cin >> N >> C;
    --C;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    
    ++A[C];    
    int ref = A[C];
    std::sort(A.begin(), A.end());
    C = std::lower_bound(A.begin(), A.end(), ref) - A.begin();
    Z S = std::accumulate(A.begin(), A.end(), Z(-1));
    std::vector<Z> f(N);
    Z prefix = S + 1, suffix = 0;
    for (int i = N - 1; i >= 0; --i) {
        prefix -= A[i];
        f[i] = S / (S - prefix) * (suffix / S + 1);
        suffix += f[i] * A[i];
    }

    std::cout << f[C] << "\n";
    return 0;
}