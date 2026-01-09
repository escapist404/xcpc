#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::set<int> set;
    while (set.contains(n) == false) {
        set.insert(n);
        int x = n, s = 0;
        do {
            s += (x % 10) * (x % 10);
            x /= 10;
        } while (x);
        n = s;
    }

    if (n == 1) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    return 0;
}