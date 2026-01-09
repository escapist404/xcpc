#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

constexpr double PI = 3.14159265358979323846;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, k;
            std::cin >> n >> k;
            std::vector<int> x(n), y(n);
            std::vector<double> ang(n);

            for (int i = 0; i < n; ++i) {
                std::cin >> x[i] >> y[i];
                ang[i] = asin(1.0 * y[i] / sqrt(1.0 * x[i] * x[i] + 1.0 * y[i] * y[i]));

                if (x[i] < 0 && y[i] >= 0) {
                    ang[i] = PI - ang[i];
                }
                if (x[i] >= 0 && y[i] < 0) {
                    ang[i] += 2 * PI;
                }
                if (x[i] < 0 && y[i] < 0) {
                    ang[i] = -ang[i];
                    ang[i] += PI;
                }
            }

            std::sort(ang.begin(), ang.end());
            for (int i = 0; i < n; ++i) {
                ang.push_back(ang[i] + 2 * PI);
            }

            double alpha = 0;
            for (int i = 0; i < 2 * n - k; ++i) {
                alpha = std::max(alpha, ang[i + k] - ang[i]);
            }

            std::cout << std::setprecision(16) << alpha << "\n";
        }();
    }
}
