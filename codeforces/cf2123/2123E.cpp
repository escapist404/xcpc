#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> count(N + 1);
            for (int i = 0; i < N; ++i) {
                int x;
                std::cin >> x;
                ++count[x];
            }
            std::vector<int> diff(N + 2);
            for (int i = 0; i <= N; ++i) {
                int left = count[i];
                int right = N - i;
                
                ++diff[left];
                --diff[right + 1];

                if (count[i] == 0) break;
            }

            for (int i = 1; i <= N; ++i) {
                diff[i] += diff[i - 1];
            }
            for (int i = 0; i <= N; ++i) {
                std::cout << diff[i] << " \n"[i == N];
            }
        }();
    }
}