#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int L, R;
    std::cin >> L >> R;

    int S = 0, T = 1;

    std::vector<std::vector<std::pair<int, int>>> adj(2);

    auto generate_node = [&]() {
        adj.push_back({});
        return adj.size() - 1;
    };

    int hl = std::__lg(L);
    int hr = std::__lg(R);
    int cur;

    if (hl == hr) {
        int idx = hl;
        while (idx >= 1 & ((L >> idx) == (R >> idx))) {
            int next = generate_node();
            adj[S].emplace_back(next, L >> idx & 1);
            --idx;
            S = next;
        }
        if (idx == 0) {
            if (L == R) {
                adj[S].emplace_back(T, L & 1);
            } else {
                adj[S].emplace_back(T, 0);
                adj[S].emplace_back(T, 1);
            }
        } else {
            int l = generate_node();
            int m = -1;
            int r = generate_node();
            adj[S].emplace_back(l, 0);
            adj[S].emplace_back(r, 1);
            for (int i = idx - 1; i >= 1; --i) {
                int nl = generate_node();
                int nm = -1;
                int nr = generate_node();

                adj[l].emplace_back(nl, (L >> i) & 1);
                if (((L >> i) & 1) == false) {
                    if (nm == -1) {
                        nm = generate_node();
                    }
                    adj[l].emplace_back(nm, 1);
                }
                adj[r].emplace_back(nr, (R >> i) & 1);
                if (((R >> i) & 1) == true) {
                    if (nm == -1) {
                        nm = generate_node();
                    }
                    adj[r].emplace_back(nm, 0);
                }
                if (m != -1) {
                    if (nm == -1) {
                        nm = generate_node();
                    }
                    adj[m].emplace_back(nm, 0);
                    adj[m].emplace_back(nm, 1);
                }

                l = nl;
                r = nr;
                m = nm;
            }

            adj[l].emplace_back(T, L & 1);
            if ((L & 1) == false) {
                adj[l].emplace_back(T, 1);
            }
            adj[r].emplace_back(T, R & 1);
            if ((R & 1) == true) {
                adj[r].emplace_back(T, 0);
            }
            if (m != -1) {
                adj[m].emplace_back(T, 0);
                adj[m].emplace_back(T, 1);
            }
        }
    } else {
        cur = S;
        std::vector<int> lchain_idx;
        for (int i = hl; i >= 1; --i) {
            int next = generate_node();
            adj[cur].emplace_back(next, L >> i & 1);
            if (i != hl && (L >> i & 1) == false) {
                if (lchain_idx.empty()) {
                    int chain = generate_node();
                    lchain_idx.resize(i + 1);
                    for (int j = i; j >= 2; --j) {
                        int next = generate_node();
                        lchain_idx[j] = chain;
                        adj[chain].emplace_back(next, 0);
                        adj[chain].emplace_back(next, 1);
                        chain = next;
                    }
                    lchain_idx[1] = chain;
                    adj[chain].emplace_back(T, 0);
                    adj[chain].emplace_back(T, 1);
                }
                adj[cur].emplace_back(lchain_idx[i], 1);
            }
            cur = next;
        }
        {
            int next = T;
            adj[cur].emplace_back(next, L & 1);
            if ((L & 1) == false) {
                adj[cur].emplace_back(T, 1);
            }
        }

        cur = S;
        std::vector<int> rchain_idx;
        for (int i = hr; i >= 1; --i) {
            int next = generate_node();
            adj[cur].emplace_back(next, R >> i & 1);
            if (i != hr && (R >> i & 1) == true) {
                if (rchain_idx.empty()) {
                    int chain = generate_node();
                    rchain_idx.resize(i + 1);
                    for (int j = i; j >= 2; --j) {
                        int next = generate_node();
                        rchain_idx[j] = chain;
                        adj[chain].emplace_back(next, 0);
                        adj[chain].emplace_back(next, 1);
                        chain = next;
                    }
                    rchain_idx[1] = chain;
                    adj[chain].emplace_back(T, 0);
                    adj[chain].emplace_back(T, 1);
                }
                adj[cur].emplace_back(rchain_idx[i], 0);
            }
            cur = next;
        }
        {
            int next = T;
            adj[cur].emplace_back(next, R & 1);
            if ((R & 1) == true) {
                adj[cur].emplace_back(T, 0);
            }
        }

        if (hr - hl >= 2) {
            std::vector<int> tchain_idx(hr);
            for (int i = hr - 1; i >= 1; --i) {
                int next = generate_node();
                tchain_idx[i] = next;
            }
            for (int i = hr - 1; i >= 2; --i) {
                adj[tchain_idx[i]].emplace_back(tchain_idx[i - 1], 0);
                adj[tchain_idx[i]].emplace_back(tchain_idx[i - 1], 1);
            }
            adj[tchain_idx[1]].emplace_back(T, 0);
            adj[tchain_idx[1]].emplace_back(T, 1);
            for (int i = hr - 1; i >= hl + 1; --i) {
                adj[S].emplace_back(tchain_idx[i], 1);
            }
        }
    }

    int n = adj.size();
    std::cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << adj[i].size() << " ";
        for (auto [j, w] : adj[i]) {
            std::cout << j + 1 << " " << w << " ";
        }
        std::cout << "\n";
    }

    return 0;
}