#include <bits/stdc++.h>

int main() {
    int N;
    std::cin >> N;

    std::vector<int> R(N), C(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> R[i] >> C[i];
    }

    std::cout << (std::max(*std::max_element(R.begin(), R.end()) - *std::min_element(R.begin(), R.end()), *std::max_element(C.begin(), C.end()) - *std::min_element(C.begin(), C.end())) + 1) / 2;
}