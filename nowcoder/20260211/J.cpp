#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>

int main() {
    std::vector<int> a(9);
    for (int i = 0; i < 9; ++i) {
        std::cin >> a[i];
    }

    if (std::set<int>(a.begin(), a.end()).size() == 9 && a[0] + a[4] + a[8] == a[2] + a[4] + a[6] && a[0] + a[1] + a[2] == a[3] + a[4] + a[5] && a[0] + a[1] + a[2] == a[6] + a[7] + a[8] && a[0] + a[3] + a[6] == a[1] + a[4] + a[7] && a[0] + a[3] + a[6] == a[2] + a[5] + a[8]) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
