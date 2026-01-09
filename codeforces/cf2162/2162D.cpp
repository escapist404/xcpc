#include <bits/stdc++.h>

namespace interactor {
int ask(int type, int l, int r) {
    std::cout << type << " " << l + 1 << " " << r << std::endl;
    int result;
    std::cin >> result;
    return result;
}
void report(int l, int r) {
    std::cout << "! " << l + 1 << " " << r << std::endl;
}
};

void solve() {
    int n;
    std::cin >> n;

    int c = interactor::ask(2, 0, n) - interactor::ask(1, 0, n);
    int l = 0, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        int d = interactor::ask(2, l, m) - interactor::ask(1, l, m);
        if (d == 0) {
            l = m;
        } else if (d == c) {
            r = m;
        } else {
            interactor::report(m - d, m + c - d);
            return;
        }
    }

    interactor::report(l, r);
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}