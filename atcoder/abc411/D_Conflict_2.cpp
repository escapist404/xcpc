#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int N, Q;
    std::cin >> N >> Q;

    std::vector<std::string> S(N + 1);
    for (int i = 0; i < Q; ++i) {
        int type;
        std::cin >> type;
        switch (type) {
            case 1: {
                int p;
                std::cin >> p;
                --p;
                S[p] = S[N];
                break;
            }
            case 2: {
                int p;
                std::string s;
                std::cin >> p >> s;
                --p;
                S[p].append(s);
                break;
            }
            case 3: {
                int p;
                std::cin >> p;
                --p;
                S[N] = S[p];
                break;
            }
        }
    }
    std::cout << S[N] << "\n";
    return 0;
}