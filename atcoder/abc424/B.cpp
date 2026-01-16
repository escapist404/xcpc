#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> s(n);
    for (int i = 0; i < k; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        s[a]++;
        if (s[a] == m) {
            std::cout << a + 1 << " ";
        }
    }

    std::cout << "\n";

    return 0;
}