#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    a[0][(n - 1) / 2] = 1;
    int r = 0, c = (n - 1) / 2;

    for (int i = 2; i <= n * n; ++i) {
        if (a[(r - 1 + n) % n][(c + 1) % n] == 0) {
            a[(r - 1 + n) % n][(c + 1) % n] = i;
            r = (r - 1 + n) % n;
            c = (c + 1) % n;
        } else {
            a[(r + 1) % n][c] = i;
            r = (r + 1) % n;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << a[i][j] << " \n"[j == n - 1];
        }
    }

    return 0;
}
