#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>

int main() {
    std::string S, T;
    std::cin >> S >> T;

    std::set<char> set;

    for (const auto i : T) set.insert(i);

    bool answer = true;
    for (int i = 1; i < (int)S.size(); ++i) {
        if (isupper(S[i])) {
            if (set.count(S[i - 1]) == 0) answer = false;
        }
    }

    if (answer) std::cout << "Yes\n";
    else std::cout << "No\n";
    
    return 0;
}