#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>

int main() {
    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> matrix(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> matrix[i];
    }

    const std::pair<int, int> d[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (matrix[i][j] == '#') {
                int count = 0;
                for (auto [x, y] : d) {
                    if (0 <= i + x && i + x < h && 0 <= j + y && j + y < w) {
                        if (matrix[i + x][j + y] == '#') {
                            ++count;
                        }
                    }
                }
                if ((count == 2 || count == 4) == false) {
                    std::cout << "No\n";
                    return 0;
                }
            }
        }
    }

    std::cout << "Yes\n";
    return 0;
}
