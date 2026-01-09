#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    const auto S = std::accumulate(A.begin(), A.end(), 0LL);
    if (S % N != 0) {
        std::cout << "-1\n";
        return 0;
    }

    const auto T = S / N;
    const auto V = 1 << N;
    std::vector<int> f(V, N), g(V), t(V);
    f[0] = 0;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < N; ++j) {
            if ((i >> j) & 1) {
                g[i] += A[j] - T;
            }
        }
        for (int j = 0; j < N; ++j) {
            if ((i >> j) & 1) {
                int prev = f[i ^ (1 << j)] + (g[i] != 0);
                if (f[i] > prev) {
                    t[i] = j;
                    f[i] = prev;
                }
            }
        }
    }

    std::vector<std::tuple<int, int, int>> op;
    int cur = (1 << N) - 1;
    while (cur) {
        std::deque<int> cand;
        do {
            cand.push_back(t[cur]);
            cur ^= 1 << t[cur];
        } while (cur != 0 && g[cur] != 0);

        std::sort(cand.begin(), cand.end(), [&A](int x, int y) { return A[x] < A[y]; });
        while (cand.size()) {
            if (A[cand.front()] == T) {
                cand.pop_front();
                continue;
            }
            if (A[cand.back()] == T) {
                cand.pop_back();
                continue;
            }
            int fr = cand.back();
            int to = cand.front();
            int d = std::min(T - A[to], A[fr] - T);
            op.emplace_back(fr + 1, to + 1, d);
            A[to] += d;
            A[fr] -= d;
        }
    }

    std::cout << op.size() << "\n";
    for (auto [x, y, z] : op) {
        std::cout << x << " " << y << " " << z << "\n";
    }

    return 0;
}