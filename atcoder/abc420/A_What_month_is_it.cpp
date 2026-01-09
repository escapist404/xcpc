#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int X, Y;
    std::cin >> X >> Y;

    --X;
    X += Y;
    X %= 12;
    X++;

    std::cout << X << "\n";
}