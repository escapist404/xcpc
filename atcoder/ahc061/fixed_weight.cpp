#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <random>
#include <chrono>

const int orientX[] = {1, 0, -1, 0};
const int orientY[] = {0, 1, 0, -1};
const int orientWays = 4;
const int maxChoose = 4;

int main() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int gridSize, playerNumber, turnNumber, levelCap;
    std::cin >> gridSize >> playerNumber >> turnNumber >> levelCap;

    std::vector<std::vector<int>> value(gridSize, std::vector<int>(gridSize));
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            std::cin >> value[i][j];
        }
    }

    std::vector<std::vector<int>> belong(gridSize, std::vector<int>(gridSize, -1));
    std::vector<std::vector<int>> level(gridSize, std::vector<int>(gridSize));
    std::vector<std::pair<int, int>> startPositions(playerNumber);
    for (int i = 0; i < playerNumber; ++i) {
        std::cin >> startPositions[i].first >> startPositions[i].second;
        level[startPositions[i].first][startPositions[i].second] = 1;
        belong[startPositions[i].first][startPositions[i].second] = i;
    }
    
    auto currentPosition = startPositions;

    double weightNoPlayer = 0.3;
    double weightSelfLess = 0.2;
    double weightSelfCap = 0;
    double weightOtherLess = 0.15;
    double weightOtherCap = 0.04;

    for (int turn = 0; turn < turnNumber; ++turn) {
        #ifndef NDEBUG
        std::cerr << "--------\nturn: " << turn << "\n--------\n" << std::endl;
        #endif
        std::vector<std::vector<int>> visit(gridSize, std::vector<int>(gridSize));
        std::queue<std::pair<int, int>> queue;
        queue.push(currentPosition[0]);
        visit[currentPosition[0].first][currentPosition[0].second] = 1;
        int candidateCount = 0;

        #ifndef NDEBUG
        std::cerr << "current position: " << currentPosition[0].first << " " << currentPosition[0].second << std::endl;
        std::cerr << "belong:" << std::endl;
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                std::cerr << belong[i][j] << " ";
            }
            std::cerr << std::endl;
        }
        #endif

        while (queue.empty() == false) {
            auto [x, y] = queue.front();
            queue.pop();
            candidateCount++;
            if (belong[x][y] != 0) {
                continue;
            }
            for (int k = 0; k < orientWays; ++k) {
                int nextX = x + orientX[k];
                int nextY = y + orientY[k];
                if (nextX < 0 || nextX >= gridSize || nextY < 0 || nextY >= gridSize) {
                    continue;
                }
                if (visit[nextX][nextY]) {
                    continue;
                }
                visit[nextX][nextY] = 1;
                queue.push({nextX, nextY});
            }
        }

        #ifndef NDEBUG
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                std::cerr << visit[i][j] << " ";
            }
            std::cerr << std::endl;
        }
        #endif
    
        for (int i = 1; i < playerNumber; ++i) {
            visit[currentPosition[i].first][currentPosition[i].second] = 0;
        }
    
        std::vector<std::tuple<double, int, int>> candidates;
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridSize; ++y) {
                if (visit[x][y] == 0) {
                    continue;
                }
                double score = value[x][y];
                if (belong[x][y] == -1) {
                    score *= weightNoPlayer;
                } else if (belong[x][y] == 0) {
                    if (level[x][y] < levelCap) {
                        score *= weightSelfLess;
                    } else {
                        score *= weightSelfCap;
                    }
                } else {
                    if (level[x][y] == 1) {
                        score *= weightOtherLess;
                    } else {
                        score *= weightOtherCap;
                    }
                }
                #ifndef NDEBUG
                std::cerr << "candidate: " << x << " " << y << " score: " << score << std::endl;
                #endif
                candidates.emplace_back(score, x, y);
            }
        }
        
        std::sort(candidates.begin(), candidates.end(), std::greater<>());
        int choose = rng() % maxChoose;
        choose = std::min(choose, (int)candidates.size() - 1);
        #ifndef NDEBUG
        std::cerr << "choose: " << choose << std::endl;
        #endif
        auto [score, x, y] = candidates[choose];
        std::cout << x << " " << y << std::endl;

        std::vector<std::pair<int, int>> targetPositions(playerNumber);
        for (int i = 0; i < playerNumber; ++i) {
            std::cin >> targetPositions[i].first >> targetPositions[i].second;
        }
        for (int i = 0; i < playerNumber; ++i) {
            std::cin >> currentPosition[i].first >> currentPosition[i].second;
        }
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                std::cin >> belong[i][j];
            }
        }
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                std::cin >> level[i][j];
            }
        }
    }

    return 0;
}
