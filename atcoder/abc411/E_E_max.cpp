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
    int N;
    std::cin >> N;
    std::vector<std::pair<int, int>> P(N * 6);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 6; ++j) {
            int value;
            std::cin >> value;
            P[i * 6 + j] = {value, i};
        }
    }

    std::sort(P.begin(), P.end());

    Z base = power(Z(1), Z(6), N);
    Z answer = 0;
    std::vector<int> count(N);
    Z mul = 0;
    int zero = N;
    bool flag = true;

    auto update = [&](const int id) {
        if (count[id]++ == 0) {
            --zero;
        }
        if (zero == 0) {
            if (flag) {
                mul = std::accumulate(count.begin(), count.end(), Z(1), [](auto x, auto y) { return y * x; });
                flag = false;
            } else {
                mul /= count[id] - 1;
                mul *= count[id];
            }
        }
    };

    Z last = 0;
    for (int i = 0; i < N * 6; ++i) {
        auto [value, id] = P[i];
        update(id);
        if (i == N * 6 || P[i + 1].first != value) {
            answer += Z(value) * (mul - last);
            last = mul;
        }
    }

    std::cout << answer / base << std::endl;
    return 0;
}
