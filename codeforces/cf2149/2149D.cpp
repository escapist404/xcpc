#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;
    
    std::vector<i64> cand;

    for (int j = 0; j < 2; ++j) {
        i64 fst = 0, lst = 0;
        int fc = 0, lc = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'b') {
                lst += i;
                lc++;
            }
        }
    
        for (int i = 0; i < n; ++i) {
            i64 la = lst - 1LL * lc * (2 * i + lc - 1) / 2;
            i64 fa = 1LL * fc * (2 * i - 1 - fc) / 2 - fst;
            cand.push_back(la + fa);
            if (s[i] == 'b') {
                fc++;
                lc--;
                fst += i;
                lst -= i;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a') {
                s[i] = 'b';
            } else {
                s[i] = 'a';
            }
        }
    }

    std::cout << *std::min_element(cand.begin(), cand.end()) << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}