#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <list>

static short n;

class Solution {
    struct Coordinate {
        short x, y;
        bool isValid() {
            return 0 <= x && x < n && 0 <= y && y < n;
        }

        Coordinate() : x(0), y(0) {}
        Coordinate(const short x, const short y) : x(x), y(y) {}
        Coordinate(std::pair<short, short> pair) {
            x = pair.first;
            y = pair.second;
        }
    };

    struct Box {
        short weight, durability;
        Box() : weight(0), durability(0) {}
        Box(const short weight, const short durability) : weight(weight), durability(durability) {}
    };

    Coordinate position;
    std::vector<char> movementSequence;
    std::list<Box*> boxCarried;
    std::vector<std::vector<Box*>> map;

    void updateBoxDurability() {
        int currentWeight = 0;
        for (auto it = boxCarried.rbegin(); it != boxCarried.rend(); ++it) {
            (*it)->durability -= currentWeight;
            assert((*it)->durability > 0);
            currentWeight += (*it)->weight;
        }
    }
    void checkEntrance() {
        if (position.x == 0 && position.y == 0) {
            for (auto it = boxCarried.begin(); it != boxCarried.end(); ++it) {
                delete *it;
            }
            boxCarried.clear();
        }
    }
    
public:
    void moveUp() {
        movementSequence.push_back('U');
        position.x--;
        updateBoxDurability();
        checkEntrance();
        assert(position.isValid());
    };
    void moveDown() {
        movementSequence.push_back('D');
        position.x++;
        updateBoxDurability();
        checkEntrance();
        assert(position.isValid());
    };
    void moveLeft() {
        movementSequence.push_back('L');
        position.y--;
        updateBoxDurability();
        checkEntrance();
        assert(position.isValid());
    };
    void moveRight() {
        movementSequence.push_back('R');
        position.y++;
        updateBoxDurability();
        checkEntrance();
        assert(position.isValid());
    };
    void carryBox() {
        movementSequence.push_back('1');
        assert(map[position.x][position.y] != nullptr);
        boxCarried.push_back(map[position.x][position.y]);
        map[position.x][position.y] = nullptr;
    }
    void placeBox() {
        movementSequence.push_back('2');
        assert(map[position.x][position.y] == nullptr);
        map[position.x][position.y] = boxCarried.back();
        boxCarried.pop_back();
    }
    auto movement() {
        return movementSequence;
    }
    Solution() : position(), movementSequence(), boxCarried(), map(n, std::vector<Box*>(n)) {}
    Solution(std::vector<std::vector<short>> W, std::vector<std::vector<short>> D) {
        map = std::vector<std::vector<Box*>>(n, std::vector<Box*>(n));
        for (short i = 0; i < n; ++i) {
            for (short j = 0; j < n; ++j) {
                if (i > 0 || j > 0) {
                    map[i][j] = new Box(W[i][j], D[i][j]);
                }
            }
        }
    }
    ~Solution() {}
};

int main() {
    std::cin >> n;

    std::vector<std::vector<short>> W(n, std::vector<short>(n)), D(n, std::vector<short>(n));

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            std::cin >> W[i][j];
        }
    }

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            std::cin >> D[i][j];
        }
    }
}