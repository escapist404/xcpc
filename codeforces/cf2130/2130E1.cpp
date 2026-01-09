#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::string par(N, '?');

            auto ask = [](const std::vector<int>& I) {
                std::cout << "? ";
                std::cout << I.size() << " ";
                for (const auto& i : I) {
                    std::cout << i + 1 << " ";
                }
                std::cout << std::endl;
                int result;
                std::cin >> result;
                return result;
            };

            std::vector<int> paired = {-2};
            while ([&]() -> bool {
                int current = paired.back() + 2;
                if (current > N - 1) return false;
                std::vector<int> q(N - current);
                std::iota(q.begin(), q.end(), current);
                return ask(q) > 0;
            }()) {
                int l = paired.back() + 2, r = N;                                                          
                int current = paired.back() + 2;
                while (l + 1 < r) {
                    int m = (l + r) / 2;
                    std::vector<int> q(m - current);
                    std::iota(q.begin(), q.end(), current);
                    int result = ask(q);

                    if (result == 0) {
                        l = m;
                    } else {
                        r = m;
                    }
                }
                paired.push_back(l - 1);
                par[l - 1] = '(';
                par[l] = ')';
            }

            int c = paired.size();

            if (c == 1) {
                int l = 0, r = N;
                while (l + 1 < r) {
                    int m = (l + r) / 2;
                    if (ask({m, 0}) == 1) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
                for (int i = 0; i <= l; ++i) {
                    par[i] = ')';
                }
                for (int i = r; i < N; ++i) {
                    par[i] = '(';
                }
            } else {
                // paired.erase(paired.begin());
                paired.push_back(N);
                for (int i = c - 1; i >= 0; --i) {
                    int l = paired[i] + 1, r = paired[i + 1];
                    int sure = paired[i];
                    if (i == 0) sure = paired[1];
                    while (l + 1 < r) {
                        int m = (l + r) / 2;
                        if (ask({sure, m}) == 1) {
                            l = m;
                        } else {
                            r = m;
                        }
                    }
                    for (int j = paired[i] + 1; j <= l && j >= 0; ++j) {
                        par[j] = ')';
                    }
                    for (int j = r; j < paired[i + 1]; ++j) {
                        par[j] = '(';
                    }
                }
            }

            std::cout << "! " << par << std::endl;
        }();
    }
}