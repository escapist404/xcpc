#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int h, w, n;
    std::cin >> h >> w >> n;

    std::vector<int> a(h * w);
    for (int i = 0; i < h * w; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> s(h);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        int idx = std::find(a.begin(), a.end(), x) - a.begin();
        if (idx == h * w || a[idx] != x) {
            continue;
        }
        s[idx / w]++;
    }

    std::cout << *std::max_element(s.begin(), s.end()) << "\n";
    return 0;
}
