#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::set<int> A;
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        A.insert(x);
    }

    int x;
    std::cin >> x;
    if (A.contains(x)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
