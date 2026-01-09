#include <vector>
#include <iostream>

int main() {
    int N;
    std::cin >> N;
    std::vector<int> D(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        std::cin >> D[i];
    }

    for (int i = 0; i < N - 1; ++i) {
        int answer = 0;
        for (int j = i; j < N - 1; ++j) {
            answer += D[j];
            std::cout << answer << " \n"[j == N - 2];
        }
    }
    return 0;
}