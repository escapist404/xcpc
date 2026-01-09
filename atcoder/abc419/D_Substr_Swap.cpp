#include <bits/stdc++.h>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::list<char> S, T;
    for (int i = 0; i < N; ++i) {
        char ch;
        std::cin >> ch;
        S.push_back(ch);
    }
    for (int i = 0; i < N; ++i) {
        char ch;
        std::cin >> ch;
        T.push_back(ch);
    }

    while (M--) {
        int L, R;
        std::cin >> L >> R;
    }
}