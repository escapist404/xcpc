#include <bits/stdc++.h>

typedef long long LL;

#define NOT_EXIST -(1ll << 48)
#define EMPTY_NUM 0
#define EMPTY_TAG 0

#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)

template <typename T>
class Tag {
public:
	T cur_f, cur_n, his_f, his_n;
	Tag(const T cur_f = EMPTY_TAG, const T cur_n = EMPTY_TAG,
		const T his_f = EMPTY_TAG, const T his_n = EMPTY_TAG)
		: cur_f(cur_f), cur_n(cur_n), his_f(his_f), his_n(his_n) {}
	void clear() { cur_f = cur_n = his_f = his_n = EMPTY_TAG; }
};

template <typename T>
class Node {
public:
	T fir_m, sec_m, his_m, sum, cnt, len;
	Tag<T> tag;

	void maintain(const Tag<T> _tag = Tag<T>()) {
		sum += _tag.cur_f * cnt + _tag.cur_n * (len - cnt);
		his_m = std::max(his_m, fir_m + _tag.his_f);
		fir_m += _tag.cur_f;
		if (sec_m != NOT_EXIST) sec_m += _tag.cur_n;

		tag.his_f = std::max(tag.his_f, tag.cur_f + _tag.his_f);
		tag.his_n = std::max(tag.his_n, tag.cur_n + _tag.his_n);
		tag.cur_f += _tag.cur_f;
		tag.cur_n += _tag.cur_n;
	}

	Node(const T fir_m = NOT_EXIST, const T sec_m = NOT_EXIST,
		 const T his_m = NOT_EXIST, const T sum = EMPTY_NUM,
		 const T cnt = EMPTY_NUM, const T len = EMPTY_NUM,
		 const Tag<T> tag = Tag<T>())
		: fir_m(fir_m),
		  sec_m(sec_m),
		  his_m(his_m),
		  sum(sum),
		  cnt(cnt),
		  len(len),
		  tag(tag) {}
};

template <typename T>
class SegmentTree {
private:
	size_t n;
	std::vector<Node<T>> p;
	std::vector<T> a;

public:
	void push_down(T x) {
		Tag<T> m_tag = p[x].tag;
		Tag<T> n_tag = Tag<T>(p[x].tag.cur_n, p[x].tag.cur_n, p[x].tag.his_n,
							  p[x].tag.his_n);
		LL max = std::max(p[ls(x)].fir_m, p[rs(x)].fir_m);
		if (p[ls(x)].fir_m == max) {
			p[ls(x)].maintain(m_tag);
		} else {
			p[ls(x)].maintain(n_tag);
		}
		if (p[rs(x)].fir_m == max) {
			p[rs(x)].maintain(m_tag);
		} else {
			p[rs(x)].maintain(n_tag);
		}
		p[x].tag.clear();
	}

	Node<T> push_up(Node<T> _ls, Node<T> _rs) {
		Node<T> cur(std::max(_ls.fir_m, _rs.fir_m), NOT_EXIST,
					std::max(_ls.his_m, _rs.his_m), _ls.sum + _rs.sum,
					EMPTY_NUM, _ls.len + _rs.len, Tag<T>());
		if (_ls.fir_m > _rs.fir_m) {
			cur.sec_m = std::max(_ls.sec_m, _rs.fir_m);
			cur.cnt = _ls.cnt;
		} else if (_ls.fir_m < _rs.fir_m) {
			cur.sec_m = std::max(_ls.fir_m, _rs.sec_m);
			cur.cnt = _rs.cnt;
		} else {
			cur.sec_m = std::max(_ls.sec_m, _rs.sec_m);
			cur.cnt = _ls.cnt + _rs.cnt;
		}
		return cur;
	}

	void build(const T l, const T r, const T x) {
		p[x].len = (r - l + 1);
		if (l == r) {
			p[x].fir_m = a[l];
			p[x].sec_m = NOT_EXIST;
			p[x].his_m = a[l];
			p[x].sum = a[l];
			p[x].cnt = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, ls(x));
		build(mid + 1, r, rs(x));
		p[x] = push_up(p[ls(x)], p[rs(x)]);
	}

	Node<T> query(const T _l, const T _r, const T l, const T r, const T x) {
		if (_l > r || _r < l) return Node<T>();
		if (_l <= l && r <= _r) {
			return p[x];
		}
		push_down(x);
		int mid = (l + r) >> 1;
		if (_r <= mid) return query(_l, _r, l, mid, ls(x));
		if (_l > mid) return query(_l, _r, mid + 1, r, rs(x));
		return push_up(query(_l, _r, l, mid, ls(x)),
					   query(_l, _r, mid + 1, r, rs(x)));
	}

	void modify_add(const T _l, const T _r, const T _k, const T l, const T r,
					const T x) {
		if (_l > r || _r < l) return;
		if (_l <= l && r <= _r) {
			p[x].maintain(Tag<T>(_k, _k, _k, _k));
			return;
		}
		push_down(x);
		int mid = (l + r) >> 1;
		if (_l <= mid) modify_add(_l, _r, _k, l, mid, ls(x));
		if (_r > mid) modify_add(_l, _r, _k, mid + 1, r, rs(x));
		p[x] = push_up(p[ls(x)], p[rs(x)]);
	}

	void modify_min(const T _l, const T _r, const T _k, const T l, const T r,
					const T x) {
		if (_l > r || _r < l || _k >= p[x].fir_m) return;
		if (_l <= l && r <= _r && _k > p[x].sec_m) {
			p[x].maintain(Tag<T>(_k - p[x].fir_m, EMPTY_TAG, _k - p[x].fir_m, EMPTY_TAG));
			return;
		}
		push_down(x);
		int mid = (l + r) >> 1;
		if (_l <= mid) modify_min(_l, _r, _k, l, mid, ls(x));
		if (_r > mid) modify_min(_l, _r, _k, mid + 1, r, rs(x));
		p[x] = push_up(p[ls(x)], p[rs(x)]);
	}

	SegmentTree(const std::vector<T> a)
		: n(a.size() - 1), p(a.size() << 2), a(a) {
		build(1, n, 1);
	}
};

using i64 = long long;

int main() {
    int n;
	std::cin >> n;

	std::vector<LL> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
        a[i] = -a[i];
	}

	SegmentTree<LL> T(a);

    int q;
    std::cin >> q;
	for (int i = 1; i <= q; ++i) {
		int l, r;
        std::cin >> l >> r;
        i64 k;
        std::cin >> k;
        auto ori = -T.query(l, r, 1, n, 1).sum;
        T.modify_add(l, r, k, 1, n, 1);
        T.modify_min(l, r, 0, 1, n, 1);
        std::cout << ori + T.query(l, r, 1, n, 1).sum << "\n";
	}

	return 0;
}