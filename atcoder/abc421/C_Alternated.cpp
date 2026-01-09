#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>

int main() {
    int N;
    std::cin >> N;
    std::string S;
    std::cin >> S;

    using i64 = long long;
    i64 answer1 = 0, answer2 = 0;
    
    for (int i = 0, c = 0; i < 2 * N; ++i) {
        if (S[i] == 'A') {
            answer1 += abs(i - 2 * c);
            answer2 += abs(i - 2 * c - 1);
            ++c;
        }
    }

    std::cout << std::min(answer1, answer2) << "\n";
    return 0;
}
