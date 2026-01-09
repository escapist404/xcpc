#include <iostream>
#include <algorithm>

int main() {
    int N;
    std::cin >> N;

    int answer = 0;
    for (int i = 0; i < N; ++i) {
        int A, B;
        std::cin >> A >> B;
        answer += (B > A);
    }

    std::cout << answer << "\n";
    return 0;
}