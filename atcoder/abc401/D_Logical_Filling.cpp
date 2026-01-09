#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int N, K;
    std::cin >> N >> K;

    std::string S;
    std::cin >> S;

    for (int i = 0; i < N; ++i) {
        if (S[i] == 'o') {
            if (i != N - 1 && S[i + 1] == '?') {
                S[i + 1] = '.';
            }
            if (i != 0 && S[i - 1] == '?') {
                S[i - 1] = '.';
            }
        }
    }

    std::vector<int> length = {0};
    for (int i = 0; i < N; ++i) {
        if (S[i] != '?') {
            if (length.back() != 0) {
                length.push_back(0);
            }
        } else {
            ++*length.rbegin();
        }
    }

    if (length.back() == 0) {
        length.pop_back();
    }

    int current = 0;
    for (auto i : length) {

    }
}