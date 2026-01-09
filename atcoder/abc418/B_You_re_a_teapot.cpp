#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

int main() {
    std::cout << std::setprecision(17);

    std::string S;
    std::cin >> S;
    int N = S.size();

    double answer = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 3; j <= N - i; ++j) {
            std::string T = S.substr(i, j);
            if (T.front() == 't' && T.back() == 't') {
                answer = std::max(answer, (double)(std::count(T.begin(), T.end(), 't') - 2) / (j - 2));
            }
        }
    }

    std::cout << answer << "\n";

    return 0;
}