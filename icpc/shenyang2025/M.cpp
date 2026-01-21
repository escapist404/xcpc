#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <deque>
#include <iomanip>

const int N = 8;
const int M = 7;

int main() {
    std::array<std::vector<int>, 2> u({std::vector<int>(N), std::vector<int>(N)});
    for (int i = 0; i < N; ++i) {
        std::cin >> u[0][i] >> u[1][i];
    }

    std::vector<int> p(N);
    std::iota(p.begin(), p.end(), 0);
    double ans = 0;

    do {
        std::vector<double> f(N);
        for (int S = 0; S < 1 << M; ++S) {
            double cur = 1;
            std::deque<int> queue(N);
            std::iota(queue.begin(), queue.end(), 0);
            for (int i = 0; i < M; ++i) {
                int a = queue[0];
                int b = queue[1];
                queue.pop_front();
                queue.pop_front();
                double s = u[a > b][p[a]] + u[a < b][p[b]];
                double s1 = u[a > b][p[a]];
                double s2 = u[a < b][p[b]];
                if ((S >> i) & 1) {
                    cur *= s1 / s;
                    queue.push_back(a);
                } else {
                    cur *= s2 / s;
                    queue.push_back(b);
                }
            }
            f[p[queue.front()]] += cur;
        }
        ans = std::max(ans, f[0]);
    } while (std::next_permutation(p.begin(), p.end()));

    std::cout << std::fixed << std::setprecision(10) << ans << "\n";
    return 0;
}
