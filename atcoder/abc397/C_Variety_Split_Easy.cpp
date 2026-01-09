#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    std::map<int, int> cnt_pre, cnt_suf;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        cnt_suf[a[i]]++;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cnt_pre[a[i]]++;
        cnt_suf[a[i]]--;
        if (cnt_suf[a[i]] == 0) {
            cnt_suf.erase(a[i]);
        }

        ans = std::max(ans, (int)(cnt_pre.size() + cnt_suf.size()));
    }

    std::cout << ans << "\n";
}
