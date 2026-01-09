#ifndef LAZY_SEGMENT_TREE_HPP
#define LAZY_SEGMENT_TREE_HPP

#include <cassert>
#include <vector>

template <typename V, typename Lazy>
class LazySegmentTree {
	int n;
	std::vector<V> value;
	std::vector<Lazy> lazy;

	constexpr inline int ls(const int x) { return x * 2 + 1; }
	constexpr inline int rs(const int x) { return x * 2 + 2; }

	constexpr void push_down(const int x) {
		value[ls(x)] += lazy[x], value[rs(x)] += lazy[x];
		lazy[ls(x)] += lazy[x], lazy[rs(x)] += lazy[x];
		lazy[x] = Lazy();
	}

	void set(const int x, const int l, const int r, const int L, const int R, const Lazy& K) {
		if (L <= l && r <= R) return value[x] += K, lazy[x] += K, void();
		int m = (l + r) / 2;
		push_down(x);
		if (L < m) set(ls(x), l, m, L, R, K);
		if (R > m) set(rs(x), m, r, L, R, K);
		value[x] = value[ls(x)] + value[rs(x)];
	}
	V get(const int x, const int l, const int r, const int L, const int R) {
		if (L <= l && r <= R) return value[x];
		int m = (l + r) / 2;
		push_down(x);
		if (R <= m) return get(ls(x), l, m, L, R);
		if (L >= m) return get(rs(x), m, r, L, R);
		return get(ls(x), l, m, L, R) + get(rs(x), m, r, L, R);
	}

public:
	void set(const int l, const int r, const Lazy& k) { set(0, 0, n, l, r, k); }
	void set(const int p, const Lazy& k) { set(p, p + 1, k); }
	void set(const Lazy& k) { value[0] += k, lazy[0] += k; }
	V get(const int l, const int r) { return get(0, 0, n, l, r); }
	V get(const int p) { return get(p, p + 1); }
	V get() { return value[0]; }

	LazySegmentTree(const int n)
		: n(n), value(n * 4), lazy(n * 4) {
		std::vector<V> init(n, V());
		auto build = [&](auto self, const int x, const int l, const int r) {
			if (l + 1 == r) return value[x] = init[l], void();
			int m = (l + r) / 2;
			self(self, this->ls(x), l, m), self(self, this->rs(x), m, r);
			value[x] = value[this->ls(x)] + value[this->rs(x)];
		};
		build(build, 0, 0, n);
	}
	LazySegmentTree(const int n, std::vector<V> init)
		: n(n), value(n * 4), lazy(n * 4) {
		assert((int)init.size() == n);
		auto build = [&](auto self, const int x, const int l, const int r) {
			if (l + 1 == r) return value[x] = init[l], void();
			int m = (l + r) / 2;
			self(self, this->ls(x), l, m), self(self, this->rs(x), m, r);
			value[x] = value[this->ls(x)] + value[this->rs(x)];
		};
		build(build, 0, 0, n);
	}
};

#endif // LAZY_SEGMENT_TREE_HPP

#ifndef MODINT_HPP
#define MODINT_HPP

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

#endif // MODINT_HPP

const int P = 998'244'353;
using Z = ModInt<int, P>;

struct Lazy {
    bool empty;
    Z value;
    Lazy(bool empty = true, Z value = 0) : empty(empty), value(value) {}
    Lazy& operator+= (const Lazy& y) {
        if (y.empty == true) {
            return *this;
        }
        empty = y.empty;
        value = y.value;
        return *this;
    }
};

struct Value {
    Z value;
    int size;
    Value(Z value = 0, int size = 1) : value(value), size(size) {}
    Value& operator+= (const Lazy& y) {
        if (y.empty == true) {
            return *this;
        }
        value = y.value * size;
        return *this;
    }
};

Value operator+ (const Value& x, const Value& y) {
    return Value(x.value + y.value, x.size + y.size);
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<int> A(N);
    for (auto& i : A) std::cin >> i;

    std::vector<Value> value(N);
    for (int i = 0; i < N; ++i) {
        value[i].value = A[i];
    }

    LazySegmentTree<Value, Lazy> T(N, value);
    for (int i = 0; i < M; ++i) {
        int L, R;
        std::cin >> L >> R;
        --L;
        auto sum = T.get(L, R).value;
        T.set(L, R, Lazy{false, sum / (R - L)});
    }

    for (int i = 0; i < N; ++i) {
        std::cout << T.get(i).value << " \n"[i == N - 1];
    }

    return 0;
}
