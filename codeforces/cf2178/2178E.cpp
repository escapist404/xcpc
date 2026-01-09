#include <bits/stdc++.h>

using i64 = long long;

namespace interactor {
i64 ask(const int l, const int r) {
    std::cout << "? " << l + 1 << " " << r << std::endl;
    i64 ret;
    std::cin >> ret;
    return ret;
}
void report(const int answer) {
    std::cout << "! " << answer << std::endl;
}
};

void solve() {
    int n;
    std::cin >> n;

    int l = 0, r = n;
    while (l < r - 1) {
        i64 s = interactor::ask(l, r);
        int dl = l, dr = r;
        while (dl < dr - 1) {
            int dm = (dl + dr) / 2;
            i64 ds = interactor::ask(l, dm);
            if (ds < s / 2) {
                dl = dm;
            } else if (ds > s / 2) {
                dr = dm;
            } else {
                dl = dm;
                dr = dm + 1;
            }
        }
        if (dl - l < r - dl) {
            r = dl;
        } else {
            l = dl;
        }
    }

    interactor::report(interactor::ask(l, r));
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
