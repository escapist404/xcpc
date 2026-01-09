#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

long long refer(int x, int y) {
    return (long long)x << 32 ^ y;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> X[i] >> Y[i];
    }

    using i64 = long long;
    i64 answer = 0;

    int x_count = 0, y_count = 0;
    std::unordered_map<long long, int> slope;
    std::unordered_map<long long, int> middle_point;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (X[i] == X[j]) {
                answer += x_count++;
            } else if (Y[i] == Y[j]) {
                answer += y_count++;
            } else {
                int f = gcd(abs(X[i] - X[j]), abs(Y[i] - Y[j]));
                int U = (Y[i] - Y[j]) / f;
                int D = (X[i] - X[j]) / f;
                if (D < 0) {
                    D = -D;
                    U = -U;
                }
                answer += slope[refer(U, D)]++;
            }
            answer -= middle_point[refer(X[i] + X[j], Y[i] + Y[j])]++;
        }
    }

    std::cout << answer << "\n";

    return 0;
}