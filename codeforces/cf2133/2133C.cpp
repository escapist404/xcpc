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
            
            auto ask = [&](int X, const std::vector<int>& S) {
                std::cout << "? " << X + 1 << " " << S.size() << " ";
                for (const auto i : S) {
                    std::cout << i + 1 << " ";
                }
                std::cout << std::endl;
                int result;
                std::cin >> result;
                return result;
            };

            auto report = [&](const std::vector<int>& S) {
                std::cout << "! " << S.size() << " ";
                for (const auto i : S) {
                    std::cout << i + 1 << " ";
                }
                std::cout << std::endl;         
            };

            std::vector<int> dis(N);
            std::vector<int> SC(N);
            std::iota(SC.begin(), SC.end(), 0);

            for (int i = 0; i < N; ++i) {
                dis[i] = ask(i, SC);
            }

            int K = *std::max_element(dis.begin(), dis.end());
            std::vector<std::vector<int>> U(K);
            for (int i = 0; i < N; ++i) {
                U[dis[i] - 1].push_back(i);
            }
            std::vector<int> S = {U[K - 1][0]};
            for (int i = K - 2; i >= 0; --i) {
                for (auto j : U[i]) {
                    if (ask(S.back(), {S.back(), j}) == 2) {
                        S.push_back(j);
                        break;
                    }
                }
            }

            report(S);
        }();
    }
}