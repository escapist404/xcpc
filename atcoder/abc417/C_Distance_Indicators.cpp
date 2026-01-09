#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <map>

int main() {
    int N;
    std::cin >> N;
    std::vector<int> A(N);

    for (auto& i : A) std::cin >> i;

    std::map<int, int> S;
    long long answer = 0;
    for (int i = 0; i < N; ++i) {
        answer += S[i - A[i]];
        S[i + A[i]]++;
    }

    std::cout << answer << "\n";

    return 0;
}