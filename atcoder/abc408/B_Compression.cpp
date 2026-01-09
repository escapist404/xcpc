#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (auto& i : A) {
        std::cin >> i;
    }

    std::sort(A.begin(), A.end());
    A.erase(std::unique(A.begin(), A.end()), A.end());

    std::cout << A.size() << "\n";
    for (int i = 0; i < (int)A.size(); ++i) {
        std::cout << A[i] << " \n"[i == (int)A.size() - 1];
    }

    return 0;
}
