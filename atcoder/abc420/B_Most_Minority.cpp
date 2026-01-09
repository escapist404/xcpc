#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::string> S(N);
    std::vector<int> score(N);

    for (auto& i : S) {
        std::cin >> i;
    }

    for (int i = 0; i < M; ++i) {
        std::string T;
        for (int j = 0; j < N; ++j) {
            T.push_back(S[j][i]);
        }
        int c[2] = {std::count(T.begin(), T.end(), '0'), std::count(T.begin(), T.end(), '1')};
        char win;
        if (c[0] > c[1]) {
            win = '1';
        } else {
            win = '0';
        }
        for (int j = 0; j < N; ++j) {
            if (T[j] == win) {
                score[j]++;
            }
        }
    }

    int max = *std::max_element(score.begin(), score.end());
    for (int i = 0; i < N; ++i) {
        if (score[i] == max) {
            std::cout << i + 1 << " ";
        }
    }

    std::cout << "\n";
}
