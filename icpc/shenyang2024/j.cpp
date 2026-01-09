#include <bits/stdc++.h>

int main() {
    std::vector<std::string> name(8);
    std::vector<int> score(8);

    for (int i = 0; i < 8; ++i) {
        std::cin >> name[i] >> score[i];
    }

    auto run = [](std::pair<std::vector<std::string>, std::vector<int>> uli) {
        auto [name, score] = uli;
        int n = name.size();
        std::vector<std::string> rn;
        std::vector<int> rs;
        for (int i = 0; i < n; i += 2) {
            if (score[i] > score[i + 1]) {
                rn.push_back(name[i]);
                rs.push_back(score[i]);
            } else {
                rn.push_back(name[i + 1]);
                rs.push_back(score[i + 1]);
            }
        }
        return std::make_pair(rn, rs);
    };

    auto [fn, fs] = run(run({name, score}));
    if (fs[0] < fs[1]) {
        std::swap(fn[0], fn[1]);
    }
    std::cout << fn[0] << " beats " << fn[1] << "\n";
}