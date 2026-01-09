#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <queue>

int main() {
    using i64 = long long;

    i64 X[2], Y[2];
    std::cin >> X[0] >> Y[0] >> X[1] >> Y[1];

    std::swap(X[0], Y[0]);
    std::swap(X[1], Y[1]);

    Y[0] = -Y[0];
    Y[1] = -Y[1];

    i64 N;
    int M, L;
    std::cin >> N >> M >> L;

    std::queue<std::pair<char, int>> queue[2];
    for (int i = 0; i < M; ++i) {
        char type;
        int times;
        std::cin >> type >> times; 
        queue[0].emplace(type, times);
    }
    for (int i = 0; i < L; ++i) {
        char type;
        int times;
        std::cin >> type >> times; 
        queue[1].emplace(type, times);
    }

    i64 answer = 0;
    while (queue[0].size() && queue[1].size()) {
        char type[2] = {queue[0].front().first, queue[1].front().first};
        int times[2] = {queue[0].front().second, queue[1].front().second};
        int length = std::min(times[0], times[1]);
        times[0] -= length;
        queue[0].front().second -= length;
        times[1] -= length;
        queue[1].front().second -= length;
        if (times[0] == 0) {
            queue[0].pop();
        }
        if (times[1] == 0) {
            queue[1].pop();
        }

        if (type[0] == 'L') {
            if (type[1] == 'L') {
                if (X[0] == X[1] && Y[0] == Y[1]) {
                    answer += length;
                }
            } else if (type[1] == 'R') {
                if (Y[0] == Y[1] && X[0] > X[1] && ((X[0] - X[1]) % 2 == 0) && (X[0] - X[1] <= 2 * length)) {
                    answer++;
                }
            } else if (type[1] == 'D') {
                if (X[0] > X[1] && Y[1] > Y[0] && X[0] - X[1] == Y[1] - Y[0] && X[0] - X[1] <= length) {
                    answer++;
                }
            } else if (type[1] == 'U') {
                if (X[0] > X[1] && Y[0] > Y[1] && X[0] - X[1] == Y[0] - Y[1] && X[0] - X[1] <= length) {
                    answer++;
                }
            }
        } else if (type[0] == 'R') {
            if (type[1] == 'L') {
                if (Y[0] == Y[1] && X[1] > X[0] && ((X[1] - X[0]) % 2 == 0) && (X[1] - X[0] <= 2 * length)) {
                    answer++;
                }
            } else if (type[1] == 'R') {
                if (X[0] == X[1] && Y[0] == Y[1]) {
                    answer += length;
                }
            } else if (type[1] == 'D') {
                if (X[1] > X[0] && Y[1] > Y[0] && X[1] - X[0] == Y[1] - Y[0] && X[1] - X[0] <= length) {
                    answer++;
                }
            } else if (type[1] == 'U') {
                if (X[1] > X[0] && Y[0] > Y[1] && X[1] - X[0] == Y[0] - Y[1] && X[1] - X[0] <= length) {
                    answer++;
                }
            }
        } else if (type[0] == 'D') {
            if (type[1] == 'L') {
                if (Y[0] > Y[1] && X[1] > X[0] && Y[0] - Y[1] == X[1] - X[0] && Y[0] - Y[1] <= length) {
                    answer++;
                }
            } else if (type[1] == 'R') {
                if (Y[0] > Y[1] && X[0] > X[1] && Y[0] - Y[1] == X[0] - X[1] && Y[0] - Y[1] <= length) {
                    answer++;
                }
            } else if (type[1] == 'D') {
                if (X[0] == X[1] && Y[0] == Y[1]) {
                    answer += length;
                }
            } else if (type[1] == 'U') {
                if (X[0] == X[1] && Y[0] > Y[1] && ((Y[0] - Y[1]) % 2 == 0) && (Y[0] - Y[1] <= 2 * length)) {
                    answer++;
                }
            }
        } else if (type[0] == 'U') {
            if (type[1] == 'L') {
                if (Y[1] > Y[0] && X[1] > X[0] && Y[1] - Y[0] == X[1] - X[0] && Y[1] - Y[0] <= length) {
                    answer++;
                }
            } else if (type[1] == 'R') {
                if (Y[1] > Y[0] && X[0] > X[1] && Y[1] - Y[0] == X[0] - X[1] && Y[1] - Y[0] <= length) {
                    answer++;
                }
            } else if (type[1] == 'D') {
                if (X[0] == X[1] && Y[1] > Y[0] && ((Y[1] - Y[0]) % 2 == 0) && (Y[1] - Y[0] <= 2 * length)) {
                    answer++;
                }
            } else if (type[1] == 'U') {
                if (X[0] == X[1] && Y[0] == Y[1]) {
                    answer += length;
                }
            }
        }

        for (int i = 0; i < 2; ++i) {
            if (type[i] == 'L') {
                X[i] -= length;
            } else if (type[i] == 'R') {
                X[i] += length;
            } else if (type[i] == 'D') {
                Y[i] -= length;
            } else if (type[i] == 'U') {
                Y[i] += length;
            }
        }
    }

    std::cout << answer << "\n";
    return 0;
}
