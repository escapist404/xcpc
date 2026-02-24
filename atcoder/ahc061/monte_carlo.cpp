#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

struct State {
    int n, m, n2, T, U;
    std::vector<int> value, owner, level;
    std::vector<int> position;
    
    std::mt19937 rng;
    
    int id(const int x, const int y) {
        return x * n + y;
    }
    
    std::pair<int, int> xy(const int id) {
        return {id / n, id % n};
    }
    
    State() {
        std::cin >> n >> m >> T >> U;
        n2 = n * n;
    
        value.resize(n2);
        owner.resize(n2, -1);
        level.resize(n2);
    
        position.resize(m);
    
        for (int i = 0; i < n2; ++i) {
            std::cin >> value[i];
        }
    
        for (int i = 0; i < m; ++i) {
            int x, y;
            std::cin >> x >> y;
    
            owner[id(x, y)] = i;
            level[id(x, y)] = 1;
            position[i] = id(x, y);
        }
    }
    
    std::vector<int> get_candidate_moves(const int player) {
        std::vector<int> visited(n2);
        std::queue<int> queue;
        
        for (int i = 0; i < n2; ++i) {
            if (owner[i] == player) {
                queue.push(i);
                visited[i] = true;
            }
        }
        
        while (queue.empty() == false) {
            int current = queue.front();
            queue.pop();
            
            if (owner[current] != player) {
                continue;
            }
            
            int x = current / n;
            int y = current % n;
            
            for (int k = 0; k < 4; ++k) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    continue;
                }
                
                int nid = id(nx, ny);
                if (visited[nid]) {
                    continue;
                }
                
                visited[nid] = true;
                queue.push(nid);
            }
        }
    
        for (int i = 0; i < m; ++i) {
            if (i == player) {
                continue;
            }
            visited[position[i]] = false;
        }
        
        std::vector<int> candidates;
        
        for (int i = 0; i < n2; ++i) {
            if (visited[i] == true) {
                candidates.push_back(i);
            }
        }
        
        return std::move(candidates);
    }
};

int main() {
    State S = State();
    S.rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());

    int n = S.n;
    int m = S.m;
    int T = S.T;
    int U = S.U;
    int n2 = S.n2;

    for (int turn = 0; turn < T; ++turn) {
        std::vector<std::vector<int>> candidates(m);
        for (int i = 0; i < m; ++i) {
            candidates[i] = S.get_candidate_moves(i);
        }
        
    }

    return 0;
}
