#include <bits/stdc++.h>

using ld = double;

void solve() {
    int tsx, tsy, tgx, tgy, asx, asy, agx, agy;
    std::cin >> tsx >> tsy >> tgx >> tgy >> asx >> asy >> agx >> agy;

    auto dis = [](ld x1, ld y1, ld x2, ld y2) {
        return sqrtl((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    };

    ld tt = dis(tsx, tsy, tgx, tgy);
    ld ta = dis(asx, asy, agx, agy);

    auto eval = [&](ld t) {
        ld tcx = tsx + std::min(tt, t) / tt * (tgx - tsx);
        ld tcy = tsy + std::min(tt, t) / tt * (tgy - tsy);
        ld acx = asx + std::min(ta, t) / ta * (agx - asx);
        ld acy = asy + std::min(ta, t) / ta * (agy - asy);
        return dis(tcx, tcy, acx, acy);
    };

    const ld eps = 1e-10;
    auto calc = [&](ld l, ld r) {
        while (r - l >= eps) {
            ld m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            auto e1 = eval(m1), e2 = eval(m2);
            if (e2 - e1 >= eps) {
                r = m2;
            } else {
                l = m1;
            }
        }
        return eval(l);
    };

    std::cout << std::fixed << std::setprecision(15) << std::min(calc(0, std::min(tt, ta)), calc(std::min(tt, ta), std::max(tt, ta))) << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}