#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <cassert>

const std::pair<int, int> orient[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int orientWays = 4;

const double EPS = 1E-4;

int gridSize, playerNumber, turnNumber, levelCap, elementSize;

using Matrix = std::vector<int>;
using Position = int;
using PositionPair = std::pair<int, int>;
using Positions = std::vector<Position>;

bool isValidPositionPair(const PositionPair& pos) {
    return pos.first >= 0 && pos.first < gridSize && pos.second >= 0 && pos.second < gridSize;
}

bool isValidPositionPair(const int x, const int y) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

bool isValidPosition(const Position& pos) {
    return pos >= 0 && pos < elementSize;
}

Position getId(int x, int y) {
    assert(isValidPositionPair(x, y));
    return x * gridSize + y;
}

Position getId(const PositionPair& pos) {
    assert(isValidPositionPair(pos));
    return pos.first * gridSize + pos.second;
}

PositionPair getPositionPair(const Position& id) {
    assert(isValidPosition(id));
    return {id / gridSize, id % gridSize};
}

int distance(const Position& a, const Position& b) {
    auto [ax, ay] = getPositionPair(a);
    auto [bx, by] = getPositionPair(b);
    return std::abs(ax - bx) + std::abs(ay - by);
}

int distance(const PositionPair& a, const PositionPair& b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

void readMatrix(Matrix& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        std::cin >> matrix[i];
    }
}

void readPositions(Positions& positions) {
    for (size_t i = 0; i < positions.size(); ++i) {
        int x, y;
        std::cin >> x >> y;
        positions[i] = x * gridSize + y;
    }
}

class State {
    std::mt19937 rng;

    Matrix value;
    Matrix belong;
    Matrix level;
    Positions positions;

    const int emptyId = -1;
    const int selfId = 0;
    int bestAIPlayerId;

    double averagedValue;
    double minGainLossThreshold = 10;

    double selfGain;
    double bestAIPlayerGain;
    double gainRatio;
    double smoothGainRatio;
    const double estimatedAlter = 0.8;
    
    const int offset = 100000;
    int currentScore;
    
    int turn;
    
    double softmaxInitialTemperature;
    const double TemperatureDecay = 0.94;

    Positions getPossibleMoves() {
        std::queue<Position> queue;
        Matrix visited(elementSize, false);

        queue.push(positions[selfId]);
        visited[positions[selfId]] = true;

        while (queue.empty() == false) {
            auto current = queue.front();
            queue.pop();

            if (belong[current] != selfId) {
                continue;
            }

            auto [currentX, currentY] = getPositionPair(current);
            for (const auto& [deltaX, deltaY] : orient) {
                int nextX = currentX + deltaX;
                int nextY = currentY + deltaY;

                if (isValidPositionPair(nextX, nextY) == false) {
                    continue;
                }

                auto nextId = getId(nextX, nextY);
                if (visited[nextId] == true) {
                    continue;
                }

                visited[nextId] = true;
                queue.push(nextId);
            }
        }

        for (int playerId = 0; playerId < playerNumber; ++playerId) {
            if (playerId == selfId) {
                continue;
            }
            if (visited[positions[playerId]] == true) {
                visited[positions[playerId]] = false;
            }
        }

        Positions possibleMoves;
        for (int elementId = 0; elementId < elementSize; ++elementId) {
            if (visited[elementId] == true) {
                possibleMoves.push_back(elementId);
            }
        }

        return std::move(possibleMoves);
    }

    double evaluateGain(const Position& move) {
        double deltaSelf;
        double deltaBestAIPlayer;

        if (belong[move] == emptyId) {
            deltaSelf = value[move];
            deltaBestAIPlayer = 0;
        } else if (belong[move] == selfId) {
            deltaSelf = (level[move] < levelCap) ? value[move] : 0;
            deltaBestAIPlayer = 0;
        } else {
            deltaSelf = value[move] * (level[move] == 1);
            deltaBestAIPlayer = (belong[move] == bestAIPlayerId) ? -value[move] : 0;
        }

        double core =  deltaSelf - smoothGainRatio * deltaBestAIPlayer;        
    }

    std::vector<std::pair<double, Position>> evaluateMoveGains(const Positions& possibleMoves) {
        size_t possibleMovesSize = possibleMoves.size();
        std::vector<std::pair<double, Position>> gains(possibleMovesSize);

        for (size_t i = 0; i < possibleMoves.size(); ++i) {
            gains[i] = {evaluateGain(possibleMoves[i]), possibleMoves[i]};
        }

        std::sort(gains.begin(), gains.end(), std::greater<>());
        return std::move(gains);
    }

    std::pair<double, int> softmaxWithTemperature(const std::vector<std::pair<double, int>>& candidates) {
        double sum = 0;
        double temperature = softmaxInitialTemperature * std::pow(TemperatureDecay, turn);
        for (const auto& [gain, move] : candidates) {
            sum += std::exp(gain / temperature);
            // std::cerr << std::exp(gain / temperature) << " ";
        }
        // std::cerr << "\n";

        double randomValue = std::uniform_real_distribution<double>(0, sum)(rng);
        double cumulativeSum = 0;
        // std::cerr << "turn: " << turn << ", temperature: " << temperature << ", sum: " << sum << std::endl;
        for (const auto& [gain, move] : candidates) {
            cumulativeSum += std::exp(gain / temperature);
            if (randomValue <= cumulativeSum) {
                return {gain, move};
            }
        }

        // std::cerr << "Warning: softmaxWithTemperature fallback triggered, returning the last candidate." << std::endl;
        return candidates.back();
    }

public:
    int getBestAIPlayerId() const {
        return bestAIPlayerId;
    }
    int getCurrentScore() const {
        return currentScore;
    }
    double getSelfGain() const {
        return selfGain;
    }
    double getBestAIPlayerGain() const {
        return bestAIPlayerGain;
    }
    double getGainRatio() const {
        return gainRatio;
    }

    Position move() {
        auto moves = getPossibleMoves();
        auto gains = evaluateMoveGains(moves);
        auto [targetGain, targetMove] = softmaxWithTemperature(gains);
        return targetMove;
    }

    void update(const Positions& targetPositions, const Positions& currentPositions, const Matrix& currentBelong, const Matrix& currentLevel) {
        positions = currentPositions;
        belong = currentBelong;
        level = currentLevel;
        turn++;

        std::vector<double> playerGains(playerNumber, 0);
        for (int elementId = 0; elementId < elementSize; ++elementId) {
            if (belong[elementId] == emptyId) {
                continue;
            } else {
                playerGains[belong[elementId]] += value[elementId] * level[elementId];
            }
        }

        selfGain = playerGains[selfId];
        bestAIPlayerId = std::max_element(playerGains.begin() + 1, playerGains.end()) - playerGains.begin();
        bestAIPlayerGain = playerGains[bestAIPlayerId];

        gainRatio = selfGain / (bestAIPlayerGain + EPS);
        currentScore = (int)(std::round(1.0 * offset * std::log2(1.0 + gainRatio)));

        double turnsRatio = 1.0 * turn / turnNumber;
        int turnsLeft = turnNumber - turn;
        double estimatedSelfGain = selfGain + estimatedAlter * averagedValue * turnsLeft;
        double estimatedBestAIPlayerGain = bestAIPlayerGain + estimatedAlter * averagedValue * turnsLeft;
        smoothGainRatio = 1.0 + turnsRatio * turnsRatio * (estimatedSelfGain / estimatedBestAIPlayerGain - 1.0);
    }

    State(const Matrix& value, const Matrix& belong, const Matrix& level, const Positions& positions)
        : value(value), belong(belong), level(level), positions(positions) {
        rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
        turn = -1;
        averagedValue = 0;
        for (int i = 0; i < elementSize; ++i) {
            averagedValue += value[i];
        }
        averagedValue /= elementSize;
        softmaxInitialTemperature = 1.0 / 3 * averagedValue;
        update({}, positions, belong, level);
    }
};


int main() {
    std::cin >> gridSize >> playerNumber >> turnNumber >> levelCap;
    elementSize = gridSize * gridSize;

    Matrix value = Matrix(elementSize);
    Matrix belong = Matrix(elementSize, -1);
    Matrix level = Matrix(elementSize);
    Positions positions(playerNumber);
    
    readMatrix(value);
    readPositions(positions);

    for (const auto& pos : positions) {
        auto [x, y] = getPositionPair(pos);
        belong[getId(x, y)] = &pos - &positions[0];
        level[getId(x, y)] = 1;
    }

    State strategy(value, belong, level, positions);
    Positions targetPositions(playerNumber);
    
    for (int turn = 0; turn < turnNumber; ++turn) {
        auto move = strategy.move();
        auto [x, y] = getPositionPair(move);

        std::cout << x << " " << y << std::endl;

        readPositions(targetPositions);
        readPositions(positions);
        readMatrix(belong);
        readMatrix(level);    

        strategy.update(targetPositions, positions, belong, level);
    }

    return 0;
}
