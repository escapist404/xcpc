#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int N, K;
    std::cin >> N >> K;
    std::vector<int> A(N + 1, 1);
    const int P = 1000000000;
    
    int current = K;
    for (int i = K; i <= N; ++i) {
        A[i] = current;
        current -= A[i - K];
        current += A[i];
        current %= P;
        current += P;
        current %= P;
    }

    std::cout << A[N] << "\n";
}