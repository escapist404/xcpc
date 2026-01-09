#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> X(N + 2);
    int answer = 0;
    for (int i = 0; i < Q; ++i) {
        int pos;
        std::cin >> pos;
        if (X[pos] == 0) {
            answer += 1 - (X[pos - 1] + X[pos + 1]);
        } else {
            answer -= 1 - (X[pos - 1] + X[pos + 1]);
        }
        X[pos] ^= 1;
        std::cout << answer << '\n';
    }
    
    return 0;
}