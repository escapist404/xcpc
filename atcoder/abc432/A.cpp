#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int v[3];
    std::cin >> v[0] >> v[1] >> v[2];
    std::sort(v, v + 3);
    std::cout << v[2] << v[1] << v[0] << "\n";

    return 0;
}
