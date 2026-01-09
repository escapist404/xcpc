#include <bits/stdc++.h>

struct BigInt {
    std::string digit;

    BigInt() {
        digit = "0";
    }

    BigInt(const std::string& s) {
        digit = s;
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
        return x.digit < y.digit;
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

int main() {
    BigInt a, b;
    std::cin >> a >> b;
    std::cout << a + b << "\n";

    return 0;
}