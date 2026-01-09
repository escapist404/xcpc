#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main() {
    using i64 = long long;
    i64 L, R;
    std::cin >> L >> R;

    std::vector<int> prime;
    std::vector<bool> visit(10000001);

    for (int i = 2; i <= 10000000; ++i) {
        if (visit[i] == false) {
            prime.push_back(i);
        }
        for (const auto j : prime) {
            if ((i64)i * j > 10000000) {
                break;
            }
            visit[i * j] = true;
            if (i % j == 0) {
                break;
            }
        }
    }

    std::vector<i64> S = {L};
    visit = std::vector<bool>(R - L + 1);
    for (const auto i : prime) {
        i64 current = i;
        while (current <= R) {
            if (current >= L) {
                S.push_back(current);
            }
            current *= i;
        }
        for (i64 j = std::max(L / i + (L % i > 0), 2LL); (i64)j * i <= R && (i64)j * i >= L; ++j) {
            visit[(i64)j * i - L] = true;
        }
    }
    for (int i = 0; i < R - L + 1; ++i) {
        if (visit[i] == false) {
            S.push_back(i + L);
        }
    }

    std::sort(S.begin(), S.end());
    S.erase(std::unique(S.begin(), S.end()), S.end());

    std::cout << S.size() << "\n";
    return 0;
}
