#include <bits/stdc++.h>

int main() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    if (c >= a && d < b) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
