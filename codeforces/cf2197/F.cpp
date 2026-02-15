#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int n;
    std::string s;

    std::cin >> n >> s;

    std::vector<int> round;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            round.push_back(i);
        }
        if (s[i] == ')') {
            if (round.empty() == false && s[round.back()] == '(') {
                round.pop_back();
            } else {
                round.push_back(i);
            }
        }
    }

    std::vector<int> square;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '[') {
            square.push_back(i);
        }
        if (s[i] == ']') {
            if (square.empty() == false && s[square.back()] == '[') {
                square.pop_back();
            } else {
                square.push_back(i);
            }
        }
    }

    std::vector<int> left = {n}, right{-1};
    for (const auto i : round) {
        if (s[i] == '(') {
            left.push_back(i);
        } else if (s[i] == ')') {
            right.push_back(i);
        }
    }
    for (const auto i : square) {
        if (s[i] == '[') {
            left.push_back(i);
        } else if (s[i] == ']') {
            right.push_back(i);
        }
    }

    int offset = *std::min_element(left.begin(), left.end()) > *std::max_element(right.begin(), right.end()) && left.size() % 2 == 0;
    std::cout << (left.size() + right.size() - 2) / 2 + offset << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
