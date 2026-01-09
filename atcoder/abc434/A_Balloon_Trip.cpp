#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int W, B;
    std::cin >> W >> B;

    std::cout << (1000 * W) / B + 1 << "\n";

    return 0;
}
