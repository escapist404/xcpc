#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <random>

int gridSize, playerNumber, turnNumber, levelCapacity, elementSize;

const int INF = 1E8;
const double EPS = 1E-3;
const double TAU = 1.5;
const int K_SAMPLE = 2;

double logistic(const double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

std::mt19937 rng;

class Model {
    int turn;
    std::vector<int> value, owner, level, position;
    std::tuple<int, int, int> beforeSimulateMove;

    int id(int x, int y) const {
        return x * gridSize + y;
    }

    std::pair<int, int> xy(int id) const {
        return {id / gridSize, id % gridSize};
    }

    std::vector<int> get_candidate() const {
        std::queue<int> queue;
        std::vector<int> visited(elementSize);

        queue.push(position[0]);
        visited[position[0]] = true;

        while (queue.empty() == false) {
            int currentId = queue.front();
            queue.pop();

            auto [currentX, currentY] = xy(currentId);
            if (owner[currentId] != 0) {
                continue;
            }

            for (int i = 0; i < 4; ++i) {
                int deltaX = "2101"[i] - '1';
                int deltaY = "1210"[i] - '1';
                int nextX = currentX + deltaX;
                int nextY = currentY + deltaY;

                if (nextX < 0 || nextX >= gridSize || nextY < 0 || nextY >= gridSize) {
                    continue;
                }

                int nextId = id(nextX, nextY);
                if (visited[nextId] == true) {
                    continue;
                }
                visited[nextId] = true;
                queue.push(nextId);
            }
        }

        for (int i = 1; i < playerNumber; ++i) {
            if (visited[position[i]] == true) {
                visited[position[i]] = false;
            }
        }

        std::vector<int> candidates;
        for (int i = 0; i < elementSize; ++i) {
            if (visited[i] == true) {
                candidates.push_back(i);
            }
        }

        return std::move(candidates);
    }

    void simulate_move(const int candidate) {
        beforeSimulateMove = {candidate, owner[candidate], level[candidate]};

        if (owner[candidate] == -1) {
            owner[candidate] = 0;
            level[candidate] = 1;
        } else if (owner[candidate] == 0) {
            if (level[candidate] < levelCapacity) {
                level[candidate]++;
            }
        } else {
            if (level[candidate] == 1) {
                owner[candidate] = 0;
            } else {
                level[candidate]--;
            }
        }
    }

    void withdraw_simulate_move() {
        auto [candidate, beforeOwner, beforeLevel] = beforeSimulateMove;
        owner[candidate] = beforeOwner;
        level[candidate] = beforeLevel;
    }

    std::vector<int> calculate_player_distance(const int player) const {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
        std::vector<int> distance(elementSize, INF);

        for (int i = 0; i < elementSize; ++i) {
            if (owner[i] == player) {
                queue.emplace(0, i);
                distance[i] = 0;
            }
        }
        while (queue.empty() == false) {
            auto [currentDistance, currentId] = queue.top();
            queue.pop();

            auto [currentX, currentY] = xy(currentId);

            for (int i = 0; i < 4; ++i) {
                int deltaX = "2101"[i] - '1';
                int deltaY = "1210"[i] - '1';
                int nextX = currentX + deltaX;
                int nextY = currentY + deltaY;

                if (nextX < 0 || nextX >= gridSize || nextY < 0 || nextY >= gridSize) {
                    continue;
                }

                int nextId = id(nextX, nextY);
                int weight = level[nextId];
                if (owner[nextId] == -1) {
                    weight = 1;
                } else if (owner[nextId] == player) {
                    weight = 0;
                }
                int alterDistance = currentDistance + weight;
                if (alterDistance < distance[nextId]) {
                    distance[nextId] = alterDistance;
                    queue.emplace(distance[nextId], nextId);
                }
            }
        }

        return distance;
    }

    double calculate_expected_score(const int player) const {
        auto distance = calculate_player_distance(player);
        int turnRemain = turnNumber - turn;

        double expectation = 0.0;
        for (int i = 0; i < elementSize; ++i) {
            expectation += value[i] * level[i] * logistic(1.0 * (turnRemain - distance[i]) / TAU);
        }

        return expectation;
    }

    double calculate_move_score(const int candidate, const double selfScore, const double bestAIScore) {
        simulate_move(candidate);

        std::vector<double> nextScore(playerNumber);
        for (int i = 0; i < playerNumber; ++i) {
            nextScore[i] = calculate_expected_score(i);
        }

        withdraw_simulate_move();

        double nextSelfScore = nextScore[0];
        double nextBestAIScore = *std::max_element(nextScore.begin() + 1, nextScore.end());

        double deltaSelfScore = nextSelfScore - selfScore;
        double deltaBestAIScore = nextBestAIScore - bestAIScore;
        
        return deltaSelfScore - selfScore / (bestAIScore + EPS) * deltaBestAIScore;
    }

    int top_k_sample(std::vector<std::pair<double, int>>& score) const {
        std::sort(score.begin(), score.end(), std::greater<std::pair<double, int>>());
        int range = std::min(K_SAMPLE, (int)score.size());
        return score[rng() % range].second;
    }

public:
    std::pair<int, int> move() {
        auto candidate = get_candidate();

        double selfScore = calculate_expected_score(0);
        double bestAIScore = -INF;
        for (int i = 1; i < playerNumber; ++i) {
            bestAIScore = std::max(bestAIScore, calculate_expected_score(i));
        }
        
        std::vector<std::pair<double, int>> score(candidate.size());
        for (int i = 0; i < (int)candidate.size(); ++i) {
            score[i] = {calculate_move_score(candidate[i], selfScore, bestAIScore), candidate[i]};
        }

        return xy(top_k_sample(score));
    }

    void update() {
        for (int i = 0; i < playerNumber; ++i) {
            int x, y;
            std::cin >> x >> y;
        }
        for (int i = 0; i < playerNumber; ++i) {
            int x, y;
            std::cin >> x >> y;
            position[i] = id(x, y);
        }
        for (int i = 0; i < elementSize; ++i) {
            std::cin >> owner[i];
        }
        for (int i = 0; i < elementSize; ++i) {
            std::cin >> level[i];
        }
        turn++;
    }

    Model() {
        std::cin >> gridSize >> playerNumber >> turnNumber >> levelCapacity;
        elementSize = gridSize * gridSize;
        turn = 0;

        value.resize(gridSize * gridSize);
        owner.resize(gridSize * gridSize, -1);
        level.resize(gridSize * gridSize, 0);
        position.resize(playerNumber);

        for (int i = 0; i < gridSize * gridSize; ++i) {
            std::cin >> value[i];
        }
        
        for (int i = 0; i < playerNumber; ++i) {
            int x, y;
            std::cin >> x >> y;
            
            owner[id(x, y)] = i;
            position[i] = id(x, y);
            level[id(x, y)] = 1;
        }
    }
};

int main() {
    rng.seed(std::random_device{}());

    auto M = Model();
    
    for (int i = 0; i < turnNumber; ++i) {
        auto [x, y] = M.move();
        std::cout << x << " " << y << std::endl;
        M.update();
    }

    return 0;
}
