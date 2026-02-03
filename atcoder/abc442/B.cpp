#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int main() {
    int q;
    std::cin >> q;

    int volume = 0;
    bool isplaying = false;
    while (q--) {
        int x;
        std::cin >> x;
        if (x == 1) {
            volume++;
        } else if (x == 2) {
            if (volume != 0) {
                volume--;
            }
        } else {
            isplaying ^= 1;
        }
        if (isplaying && volume >= 3) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}
