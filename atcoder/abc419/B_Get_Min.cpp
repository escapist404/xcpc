#include <bits/stdc++.h>

int main() {
    int Q;
    std::cin >> Q;

    std::multiset<int> S;
    while (Q--) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int x;
            std::cin >> x;
            S.insert(x);
        } else {
            std::cout << *S.begin() << "\n";
            S.erase(S.begin());
        }
    }
}