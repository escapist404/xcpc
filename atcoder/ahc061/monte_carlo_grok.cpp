#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <cassert>
#include <set>
#include <iomanip>
#include <cstring>

using namespace std;

const int N = 10;
const int MAX_M = 8;
const int MAX_H = 1280;  // 4^4 * 5

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

vector<double> w_vals = {0.3, 0.5, 0.7, 0.9};
vector<double> eps_vals = {0.1, 0.2, 0.3, 0.4, 0.5};

struct Hyp {
    double wa, wb, wc, wd, eps;
};

vector<Hyp> hyps;

void init_hypotheses() {
    for (double wa : w_vals)
    for (double wb : w_vals)
    for (double wc : w_vals)
    for (double wd : w_vals)
    for (double eps : eps_vals) {
        hyps.push_back({wa, wb, wc, wd, eps});
    }
    assert(hyps.size() == MAX_H);
}

int n, m, T, U;
int V[N][N];
int owner[N][N], level[N][N];
pair<int,int> piece[MAX_M];

vector<double> log_posterior[MAX_M];  // per AI p=1..m-1

mt19937 rng(42);  // fixed seed for reproducibility

// ────────────────────────────────────────────────
// 1. 可移动范围计算
// ────────────────────────────────────────────────

vector<pair<int,int>> get_reachable(int p) {
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    queue<pair<int,int>> q;
    auto [sx, sy] = piece[p];
    q.push({sx, sy});
    vis[sx][sy] = true;
    vector<pair<int,int>> res;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        res.emplace_back(x, y);
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                !vis[nx][ny] && owner[nx][ny] == p) {
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return res;
}

vector<pair<int,int>> get_possible(int p) {
    auto reach = get_reachable(p);
    set<pair<int,int>> cand;
    for (auto [x, y] : reach) {
        cand.emplace(x, y);
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n)
                cand.emplace(nx, ny);
        }
    }
    vector<pair<int,int>> B;
    for (auto pos : cand) {
        bool blocked = false;
        for (int q = 0; q < m; ++q) {
            if (q != p && piece[q] == pos) {
                blocked = true;
                break;
            }
        }
        if (!blocked) B.push_back(pos);
    }
    return B;
}

// ────────────────────────────────────────────────
// 2. A 值计算
// ────────────────────────────────────────────────

double eval_A(const Hyp& h, int x, int y, int p) {
    int o = owner[x][y];
    if (o == -1) return V[x][y] * h.wa;
    if (o == p) return (level[x][y] < U) ? V[x][y] * h.wb : 0.0;
    return V[x][y] * ((level[x][y] == 1) ? h.wc : h.wd);
}

// ────────────────────────────────────────────────
// 3. 后验更新（贝叶斯）
// ────────────────────────────────────────────────

void update_ai(int p, pair<int,int> chosen, const vector<pair<int,int>>& B) {
    for (int h = 0; h < MAX_H; ++h) {
        const auto& hyp = hyps[h];
        double max_a = -1e100;
        int cnt_max = 0;
        vector<double> A(B.size());
        for (int i = 0; i < (int)B.size(); ++i) {
            auto [x, y] = B[i];
            A[i] = eval_A(hyp, x, y, p);
            if (A[i] > max_a + 1e-9) {
                max_a = A[i];
                cnt_max = 1;
            } else if (abs(A[i] - max_a) < 1e-9) {
                ++cnt_max;
            }
        }
        double prob = hyp.eps / (double)B.size();
        bool is_max = false;
        for (int i = 0; i < (int)B.size(); ++i) {
            if (B[i] == chosen && abs(A[i] - max_a) < 1e-9) {
                is_max = true;
                break;
            }
        }
        if (is_max) prob += (1.0 - hyp.eps) / cnt_max;
        log_posterior[p][h] += log(max(prob, 1e-12));
    }
}

// ────────────────────────────────────────────────
// 4. 获取行动概率分布
// ────────────────────────────────────────────────

vector<double> get_action_probs(int p, const vector<pair<int,int>>& B) {
    if (B.empty()) return {};

    double max_log = *max_element(log_posterior[p].begin(), log_posterior[p].end());
    double sum_e = 0.0;
    vector<double> w(MAX_H);
    for (int h = 0; h < MAX_H; ++h) {
        double e = exp(log_posterior[p][h] - max_log);
        w[h] = e;
        sum_e += e;
    }
    for (double& v : w) v /= sum_e;

    vector<double> prob(B.size(), 0.0);
    for (int h = 0; h < MAX_H; ++h) {
        if (w[h] < 1e-12) continue;
        const auto& hyp = hyps[h];
        double max_a = -1e100;
        int cnt_max = 0;
        vector<double> A(B.size());
        for (size_t i = 0; i < B.size(); ++i) {
            auto [x, y] = B[i];
            A[i] = eval_A(hyp, x, y, p);
            if (A[i] > max_a + 1e-9) {
                max_a = A[i]; cnt_max = 1;
            } else if (abs(A[i] - max_a) < 1e-9) {
                ++cnt_max;
            }
        }
        double base_rand = hyp.eps / (double)B.size();
        for (size_t i = 0; i < B.size(); ++i) {
            double pr = base_rand;
            if (abs(A[i] - max_a) < 1e-9)
                pr += (1.0 - hyp.eps) / cnt_max;
            prob[i] += w[h] * pr;
        }
    }
    return prob;
}

// ────────────────────────────────────────────────
// 5. 一回合完整模拟
// ────────────────────────────────────────────────

struct SimState {
    int new_owner[N][N];
    int new_level[N][N];
    pair<int,int> new_piece[MAX_M];
};

SimState simulate(const vector<pair<int,int>>& targets) {
    SimState s;
    memcpy(s.new_owner, owner, sizeof(owner));
    memcpy(s.new_level, level, sizeof(level));
    memcpy(s.new_piece, piece, sizeof(piece));

    vector<vector<vector<int>>> arrived(N, vector<vector<int>>(N));
    for (int p = 0; p < m; ++p) {
        auto [tx, ty] = targets[p];
        arrived[tx][ty].push_back(p);
    }

    // Conflict resolution
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto& vec = arrived[i][j];
            if (vec.size() < 2) continue;
            int o = owner[i][j];
            bool has_owner = false;
            for (int pl : vec) if (pl == o) { has_owner = true; break; }
            if (has_owner && o != -1) {
                vec = {o};
            } else {
                vec.clear();
            }
        }
    }

    // Territory update & attack
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto& vec = arrived[i][j];
            if (vec.size() != 1) continue;
            int p = vec[0];
            int o = s.new_owner[i][j];
            if (o == -1) {
                s.new_owner[i][j] = p;
                s.new_level[i][j] = 1;
            } else if (o == p) {
                s.new_level[i][j] = min(U, s.new_level[i][j] + 1);
            } else {
                s.new_level[i][j]--;
                if (s.new_level[i][j] <= 0) {
                    s.new_owner[i][j] = p;
                    s.new_level[i][j] = 1;
                } else {
                    vec.clear();  // attacker removed
                }
            }
        }
    }

    // Piece restoration
    vector<bool> alive(m, false);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (arrived[i][j].size() == 1) {
                int p = arrived[i][j][0];
                alive[p] = true;
                s.new_piece[p] = {i, j};
            }
    for (int p = 0; p < m; ++p)
        if (!alive[p]) s.new_piece[p] = piece[p];

    return s;
}

double evaluate(const SimState& s) {
    vector<double> total(m, 0.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int o = s.new_owner[i][j];
            if (o >= 0) total[o] += V[i][j];
        }
    double s0 = total[0];
    double sa = 0;
    for (int p = 1; p < m; ++p) sa = max(sa, total[p]);
    return s0 / (sa + 1e-9);
}

// ────────────────────────────────────────────────
// 主逻辑
// ────────────────────────────────────────────────

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    init_hypotheses();

    cin >> n >> m >> T >> U;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> V[i][j];

    memset(owner, -1, sizeof(owner));
    for (int p = 0; p < m; ++p) {
        int x, y;
        cin >> x >> y;
        piece[p] = {x, y};
        owner[x][y] = p;
        level[x][y] = 1;
    }

    for (int p = 1; p < m; ++p)
        log_posterior[p].assign(MAX_H, log(1.0 / MAX_H));

    for (int turn = 1; turn <= T; ++turn) {
        auto my_moves = get_possible(0);

        vector<vector<pair<int,int>>> ai_possible(m);
        vector<vector<double>> ai_prob(m);
        for (int p = 1; p < m; ++p) {
            ai_possible[p] = get_possible(p);
            ai_prob[p] = get_action_probs(p, ai_possible[p]);
        }

        pair<int,int> best_pos = my_moves[0];
        double best_exp = -1e100;
        int n_sample = (turn <= 20) ? 80 : 40;  // early more samples

        for (auto cand : my_moves) {
            double sum_r = 0.0;
            for (int s = 0; s < n_sample; ++s) {
                vector<pair<int,int>> this_turn(m);
                this_turn[0] = cand;
                for (int p = 1; p < m; ++p) {
                    if (ai_possible[p].empty()) {
                        this_turn[p] = piece[p];
                        continue;
                    }
                    discrete_distribution<int> dist(ai_prob[p].begin(), ai_prob[p].end());
                    int idx = dist(rng);
                    this_turn[p] = ai_possible[p][idx];
                }
                auto after = simulate(this_turn);
                sum_r += evaluate(after);
            }
            double avg = sum_r / n_sample;
            if (avg > best_exp + 1e-9) {
                best_exp = avg;
                best_pos = cand;
            }
        }

        // 输出并刷新
        cout << best_pos.first << " " << best_pos.second << endl;
        cout.flush();

        // 读入本回合结果
        vector<pair<int,int>> chosen(m);
        for (int p = 0; p < m; ++p) {
            int x, y; cin >> x >> y;
            chosen[p] = {x, y};
        }
        for (int p = 0; p < m; ++p) {
            int x, y; cin >> x >> y;
            piece[p] = {x, y};
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) cin >> owner[i][j];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) cin >> level[i][j];

        // 更新 AI 后验（使用本回合开始前的 B）
        if (turn < T) {  // 最后一回合不用更新
            for (int p = 1; p < m; ++p) {
                update_ai(p, chosen[p], ai_possible[p]);
            }
        }
    }

    return 0;
}
