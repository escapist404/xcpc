#include <bits/stdc++.h>

struct BigInt {
    std::string digit;

    BigInt() {
        digit = "0";
    }

    BigInt(const std::string& s) {
        digit = s;
        std::reverse(digit.begin(), digit.end());
    }

    BigInt& operator+=(const BigInt& x) {
        auto as = [](char x, char y, char z) {
            int u = x - '0';
            int v = y - '0';
            int w = z - '0';
            return std::make_pair((char)((u + v + w) % 10 + '0'), (char)((u + v + w) / 10 + '0'));
        };

        char cur = '0';
        while (digit.size() <= x.digit.size()) {
            digit.push_back('0');
        }

        for (int i = 0; i < (int)x.digit.size(); ++i) {
            auto [res, to] = as(digit[i], x.digit[i], cur);
            digit[i] = res;
            cur = to;
        }
        for (int i = x.digit.size(); i < digit.size(); ++i) {
            auto [res, to] = as(digit[i], '0', cur);
            digit[i] = res;
            cur = to;
        }

        while (digit.back() == '0' && digit.size() > 1) {
            digit.pop_back();
        }

        return *this;
    }

    friend BigInt operator+(const BigInt& x, const BigInt& y) {
        auto res = x;
        res += y;
        return res;
    }

    friend bool operator<(const BigInt& x, const BigInt& y) {
        if (x.digit.size() > y.digit.size()) {
            return false;
        } else if (x.digit.size() < y.digit.size()) {
            return true;
        }
        for (int i = x.digit.size() - 1; i >= 0; --i) {
            if (x.digit[i] < y.digit[i]) {
                return true;
            } else if (x.digit[i] > y.digit[i]) {
                return false;
            }
        }
        return false;
    }

    friend bool operator>(const BigInt& x, const BigInt& y) {
        return y < x;
    }

    friend std::istream& operator>>(std::istream& is, BigInt& x) {
        std::string s;
        is >> s;
        std::reverse(s.begin(), s.end());
        x.digit = s;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& x) {
        for (int i = (int)x.digit.size() - 1; i >= 0; --i) {
            os << x.digit[i];
        }
        return os;
    }
};

void solve() {
    int n, K;
    std::cin >> n >> K;
    ++K;

    BigInt s;
    std::cin >> s;
    auto r = s.digit;
    std::reverse(r.begin(), r.end());

    BigInt ans;
    bool is = false;
    std::vector<int> stack;

    auto dfs = [&](auto& self, int dep, int summ, int t, int k, int lst) -> void {
        if (dep == 0) {
            if (summ != n) {
                return;
            }
            BigInt sum;
            int sum1 = 0;
            for (int i = 0; i < k; ++i) {
                sum += BigInt(r.substr(sum1, stack[i]));
                sum1 += stack[i];
            }

            if (is == false) {
                is = true;
                ans = sum;
            } else if (sum < ans) {
                ans = sum;
            }

            return;
        }

        for (int i = std::max(t - 1, 1); i < t + 2; ++i) {
            summ += i;
            if (abs(i - lst) > 1) {
                summ -= i;
                continue;
            }
            if (summ + (dep - 1) * std::max(t - 1, 1) > n) {
                summ -= i;
                break;
            }
            if (summ + (dep - 1) * (t + 1) < n) {
                summ -= i;
                continue;
            }
            stack.push_back(i);
            self(self, dep - 1, summ, t, k, i);
            stack.pop_back();
            summ -= i;
        }

        return;
    };

    int T = n / K;
    dfs(dfs, K, 0, T, K, T);
    dfs(dfs, K, 0, T + 1, K, T + 1);
    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}