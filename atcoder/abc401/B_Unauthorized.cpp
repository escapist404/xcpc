#include <vector>
#include <iostream>

int main() {
    int N;
    std::cin >> N;
    bool state = false;
    int answer = 0;
    while (N--) {
        std::string S;
        std::cin >> S;
        if (S == "login") {
            state = true;
        } else if (S == "logout") {
            state = false;
        } else if (S == "private") {
            if (state == false) {
                answer++;
            }
        }
    }

    std::cout << answer << "\n";
}