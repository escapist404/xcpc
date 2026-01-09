#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> mat(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> mat[i];
    }

    std::set<std::vector<std::string>> s;
    for (int i = 0; i <= n - m; ++i) {
        for (int j = 0; j <= n - m; ++j) {
            std::vector<std::string> c;
            for (int k = 0; k < m; ++k) {
                c.push_back(mat[i + k].substr(j, m));
            }
            s.insert(c);
        }
    }

    std::cout << s.size() << "\n";
    return 0;
}