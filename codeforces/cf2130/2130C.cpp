#include <vector>
#include <iostream>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            std::cin.tie(nullptr)->sync_with_stdio(false);
            int N;
            std::cin >> N;
            std::vector<std::pair<int, int>> seg(N), far(2 * N, {-1, -1});
            {
                int i = 0;
                for (auto& [a, b] : seg) {
                    std::cin >> a >> b;
                    --a, --b;
                    if (b > far[a].first) {
                        far[a] = {b, i};
                    }
                    ++i;
                }
            }

            int current = -1;
            std::vector<int> seq;
            for (int i = 0; i < 2 * N; ++i) {
                int next = far[i].first;
                if (next > current) {
                    seq.push_back(far[i].second + 1);
                    current = next;
                }
            }

            std::cout << seq.size() << "\n";
            for (auto i : seq) {
                std::cout << i << " ";
            }
            std::cout << "\n";
        }();
    }
}
