#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename V, typename L>
class LazySegmentTree {
    int n;
    std::vector<V> value;
    std::vector<L> lazy;

    void push(const int ix) {
        value[2 * ix + 1] += lazy[ix];
        value[2 * ix + 2] += lazy[ix];
        lazy[2 * ix + 1] += lazy[ix];
        lazy[2 * ix + 2] += lazy[ix];
        lazy[ix] = L();
    }

    void pull(const int ix) {
        value[ix] = value[2 * ix + 1] + value[2 * ix + 2];
    }

    void set(const int ix, const int il, const int ir, const int l, const int r, const L& t) {
        if (l <= il && ir <= r) {
            value[ix] += t;
            lazy[ix] += t;
            return;
        }
        push(ix);
        int im = (il + ir) / 2;
        if (r > im) {
            set(2 * ix + 2, im, ir, l, r, t);
        }
        if (l < im) {
            set(2 * ix + 1, il, im, l, r, t);
        }
        pull(ix);
    }

    V get(const int ix, const int il, const int ir, const int l, const int r) {
        if (l <= il && ir <= r) {
            return value[ix];
        }
        push(ix);
        int im = (il + ir) / 2;
        if (r <= im) {
            return get(2 * ix + 1, il, im, l, r);
        }
        if (l >= im) {
            return get(2 * ix + 2, im, ir, l, r);
        }
        return get(2 * ix + 1, il, im, l, r) + get(2 * ix + 2, im, ir, l, r);
    }

  public:
    LazySegmentTree(const int n) : n(n), value(4 * n), lazy(4 * n) {
        auto build = [&](auto& self, const int ix, const int il, const int ir) -> void {
            if (il + 1 == ir) {
                value[ix] = V();
                lazy[ix] = L();
                return;
            }
            int im = (il + ir) / 2;
            self(self, 2 * ix + 1, il, im);
            self(self, 2 * ix + 2, im, ir);
            pull(ix);
        };
        build(build, 0, 0, n);
    }
    LazySegmentTree(const std::vector<V>& info) : n(info.size()), value(4 * n), lazy(4 * n) {
        auto build = [&](auto& self, const int ix, const int il, const int ir) -> void {
            if (il + 1 == ir) {
                value[ix] = info[il];
                lazy[ix] = L();
                return;
            }
            int im = (il + ir) / 2;
            self(self, 2 * ix + 1, il, im);
            self(self, 2 * ix + 2, im, ir);
            pull(ix);
        };
        build(build, 0, 0, n);
    }
    void set(const int l, const int r, const L& t) {
        set(0, 0, n, l, r, t);
    }
    V get(const int l, const int r) {
        return get(0, 0, n, l, r);
    }
};

using i64 = long long;

struct Value {
    int up, size;
    i64 max;
    Value() : up(0), size(0), max(0LL) {}
    Value(const int up, const int size, const i64 max) : up(up), size(size), max(max) {}
};

struct Lazy {
    int flip;
    i64 add;
    Lazy() : flip(0), add(0LL) {};
    Lazy(const int flip, const i64 add) : flip(flip), add(add) {}
};

Value operator+(const Value& l, const Value& r) {
    return Value(l.up + r.up, l.size + r.size, std::max(l.max, r.max));
}

Value& operator+=(Value& l, const Lazy& r) {
    if (r.flip) {
        if (r.flip & 1) {
            l.up = l.size - l.up;
        }
        l.max = 0;
    }
    if (l.up) {
        l.max += r.add;
    } else {
        l.max = 0;
    }
    return l;
}

Lazy& operator+=(Lazy& l, const Lazy& r) {
    if (r.flip) {
        l.add = 0;
    }
    l.flip += r.flip;
    l.add += r.add;
    return l;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    LazySegmentTree<Value, Lazy> seg(std::vector<Value>(n, Value(1, 1, 0)));
    
    while (q--) {
        int type, l, r;
        std::cin >> type >> l >> r;
        --l;
        if (type == 1) {
            int x;
            std::cin >> x;
            seg.set(l, r, Lazy(0, x));
        } else if (type == 2) {
            seg.set(l, r, Lazy(1, 0));
        } else {
            std::cout << seg.get(l, r).max << "\n";
        }
    }

    return 0;
}
