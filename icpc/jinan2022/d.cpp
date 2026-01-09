#include <bits/stdc++.h>

using i64 = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    while (n--) {
        int final_pass, final_penal;
        std::cin >> final_pass >> final_penal;

        bool exist = false;
        std::vector<std::tuple<char, int, int>> frozen(m);
        for (int i = 0; i < m; ++i) {
            auto& [type, x, y] = frozen[i];
            std::cin >> type;
            switch (type) {
                case '+': {
                    char tmp;
                    std::cin >> x >> tmp >> y;
                    break;
                }
                case '?': {
                    std::cin >> x >> y;
                    break;
                }
                case '-': {
                    std::cin >> x;
                    break;
                }
                case '.': {
                    break;
                }
            }
        }
        for (int S = 0; S < 1 << m; ++S) {
            if (__builtin_popcount(S) != final_pass) {
                continue;
            }

            bool ok = true;
            int penal_lb = 0, penal_rb = 0;
            for (int i = 0; i < m; ++i) {
                auto [type, x, y] = frozen[i];
                bool passed = (S >> i) & 1;

                if (passed == 0 && type == '+') {
                    ok = false;
                    break;
                }
                if (passed == 1 && type == '-') {
                    ok = false;
                    break;
                }
                if (passed == 1 && type == '.') {
                    ok = false;
                    break;
                }

                if (passed == 0) {
                    continue;
                }
                if (type == '+') {
                    int cur_penal = y + 20 * (x - 1);
                    penal_lb += cur_penal;
                    penal_rb += cur_penal;
                } else {
                    int cur_penal_lb = 240 + 20 * (y - x);
                    int cur_penal_rb = 299 + 20 * (y - 1);
                    penal_lb += cur_penal_lb;
                    penal_rb += cur_penal_rb;
                }
            }

            if (ok && penal_lb <= final_penal && penal_rb >= final_penal) {
                std::cout << "Yes\n";
                exist = true;

                std::vector<std::tuple<char, int, int>> final(m);

                for (int i = 0; i < m; ++i) {
                    auto [type, x, y] = frozen[i];
                    if (type == '?') {
                        bool passed = (S >> i) & 1;
                        if (passed == false) {
                            final[i] = {'-', y, 0};
                            continue;
                        }

                        int cur_penal_lb = 240 + 20 * (y - x);
                        int cur_penal_rb = 299 + 20 * (y - 1);
                        if (final_penal - penal_lb < cur_penal_rb - cur_penal_lb) {
                            int diff = final_penal - penal_lb;
                            int dirt = diff / 20, pass_time = 240;
                            if (dirt < x - 1) {
                                final[i] = {'+', y - x + dirt + 1, pass_time + diff % 20};
                            } else {
                                final[i] = {'+', y, pass_time + diff - 20 * (x - 1)};
                            }
                        } else {
                            final[i] = {'+', y, 299};
                        }
                        penal_lb += std::min(final_penal - penal_lb, cur_penal_rb - cur_penal_lb);
                    } else {
                        final[i] = frozen[i];
                    }
                }

                for (int i = 0; i < m; ++i) {
                    auto [type, x, y] = final[i];
                    std::cout << type;
                    switch (type) {
                        case '+': {
                            std::cout << " " << x << "/" << y << "\n";
                            break;
                        }
                        case '-': {
                            std::cout << " " << x << "\n";
                            break;
                        }
                        case '.': {
                            std::cout << "\n";
                            break;
                        }
                    }
                }
                break;
            }
        }

        if (exist == false) {
            std::cout << "No\n";
        }
    }

    return 0;
}
