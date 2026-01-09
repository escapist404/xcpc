#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int a, b;
    std::cin >> a >> b;
    b = -b;
    ++b;
    if (b == 9) {
        b = 1;
        ++a;
    }
    std::cout << a << "-" << b << "\n";
    return 0;
}
