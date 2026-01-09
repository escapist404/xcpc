#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

signed main() {
    freopen("in.in", "w", stdout);
    int T = 55;
    cout << T << endl;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= i; j++) {
            cout << i << ' ' << j << '\n';
        }
    }
}