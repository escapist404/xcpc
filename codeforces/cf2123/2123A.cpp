#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            int c[] = {0, 0, 0, 0};
            for (int i = 0; i < N; ++i) {
                ++c[i % 4];
            }
            if (c[0] == c[3] && c[1] == c[2]) {
                std::cout << "Bob\n";
            } else {
                std::cout << "Alice\n";
            }
        }();
    }
    
}