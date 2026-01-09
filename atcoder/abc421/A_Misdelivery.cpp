#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>

int main() {
    int N;
    std::cin >> N;

    std::vector<std::string> map(N);
    for (int i = 0; i < N; ++i) {
        std::string S;
        std::cin >> S;
        map[i] = S;
    } 

    int X;
    std::string Y;
    std::cin >> X >> Y;
    if (map[X - 1] == Y) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}