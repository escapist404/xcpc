#include <bits/stdc++.h>

int main() {
    int s, a, b, x;
    std::cin >> s >> a >> b >> x;

    int ans = 0;
    while (x > a + b) {
        x -= a + b;
        ans += s * a;
    }

    ans += s * std::min(x, a);
    std::cout << ans << "\n";
    return 0;
}