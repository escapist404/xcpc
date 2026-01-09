#include <bits/stdc++.h>
#include "atcoder/convolution.hpp"

const int P = 998244353;

int power(int base, int exp) {
    int ret = 1;
    while (exp) {
        if (exp & 1) {
            ret = 1LL * ret * base % P;
        }
        base = 1LL * base * base % P;
        exp >>= 1;
    }
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> A(N);
    std::vector<int> B(M);

    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    for (int i = 0; i < M; ++i) {
        std::cin >> B[i];
    }
    
    const int S = 5E5;
    std::vector<int> count1(S + 1), count2(S + 1);
    for (int i = 0; i < N; ++i) {
        count1[A[i]]++;
    }
    for (int i = 0; i < M; ++i) {
        count2[B[i]]++;
    }

    std::vector<int> U(S + 1), V(S + 1);
    V[S] = 1;
    for (int i = 1; i <= S; ++i) {
        V[S] = 1LL * V[S] * i % P;
    }
    V[S] = power(V[S], P - 2);
    for (int i = S - 1; i >= 0; --i) {
        V[i] = 1LL * V[i + 1] * (i + 1) % P;
    }

    U = V;
    for (int i = 0; i <= S; ++i) {
        U[i] = 1LL * U[i] * count2[i] % P;
    }

    int ans = 0;
    auto R = atcoder::convolution<P, int>(U, V);
    for (int i = 1, f = 1; i <= S; ++i) {
        f = 1LL * f * i % P;
        ans += 1LL * count1[i] * f % P * R[i] % P;
        ans %= P;
    }

    std::cout << ans << "\n";

    return 0;
}