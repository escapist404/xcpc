#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <utility>

const std::string HEX2BIN_MAP[] = {
    "0000", "0001", "0010", "0011", 
    "0100", "0101", "0110", "0111", 
    "1000", "1001", "1010", "1011", 
    "1100", "1101", "1110", "1111", 
};


struct Table {
    int staticSize, dynamicSize;
    std::vector<std::pair<std::string, std::string>> staticTable;
    std::deque<std::pair<std::string, std::string>> dynamicTable;

    Table(int staticSize, int dynamicSize, const std::vector<std::pair<std::string, std::string>>& staticTable)
        : staticSize(staticSize), dynamicSize(dynamicSize), staticTable(staticTable) {
            for (int i = 0; i < dynamicSize; ++i) {
                dynamicTable.emplace_back("", "");
            }
        }

    std::pair<std::string, std::string> operator[](const size_t idx) const {
        if (idx >= staticSize) {
            return dynamicTable[idx - staticSize];
        } else {
            return staticTable[idx];
        }
    }

    std::pair<std::string, std::string>& operator[](const size_t idx) {
        if (idx >= staticSize) {
            return dynamicTable[idx - staticSize];
        } else {
            return staticTable[idx];
        }
    }

    void insert(const std::pair<std::string, std::string>& pair) {
        dynamicTable.pop_back();
        dynamicTable.push_front(pair);
    }

    void insert(const std::string& key, const std::string& value) {
        insert({key, value});
    }
};

std::ostream& operator<<(std::ostream& os, const std::pair<std::string, std::string>& con) {
    os << con.first << ": " << con.second;
    return os;
}

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char d) : data(d), left(nullptr), right(nullptr) {}
    Node() : data('\0'), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left, right;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int s, d;
    std::cin >> s >> d;

    std::vector<std::pair<std::string, std::string>> staticTable(s);
    for (int i = 0; i < s; ++i) {
        std::string key, value;
        std::cin >> key >> value;
        staticTable[i] = {key, value};
    }

    Table table(s, d, staticTable);

    std::string H;
    std::cin >> H;

    auto buildHuffmanTree = [&, idx = 0](auto& self) mutable -> Node* {
        if (H[idx++] == '1') {
            return new Node(H[idx++]);
        } else {
            Node* cur = new Node();
            cur->left = self(self);
            cur->right = self(self);
            return cur;
        }
    };

    Node* root = buildHuffmanTree(buildHuffmanTree);

    auto decodeFromBinary = [&](const std::string& s) -> std::string {
        Node* cur = root;
        std::string result;
        for (const auto& ch : s) {
            if (cur->left == nullptr && cur->right == nullptr) {
                result.push_back(cur->data);
                cur = root;
            }
            if (ch == '0') {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        if (cur->left == nullptr && cur->right == nullptr) {
            result.push_back(cur->data);
            cur = root;
        }
        return result;
    };

    auto hex2Bin = [](const std::string& s) -> std::string {
        std::string result;
        for (const auto& i : s) {
            int v;
            if ('0' <= i && i <= '9') {
                v = i - '0';
            } else {
                v = i - 'a' + 10;
            }
            result += HEX2BIN_MAP[v];
        }
        return result;
    };

    auto alter = [&](const std::string& s) -> std::string {
        if (s.size() == 0) {
            return "";
        }
        if (s[0] == 'H') {
            if (s[1] == 'H') {
                return s.substr(1);
            } else {
                auto t = hex2Bin(s);
                auto shift = t.substr((int)t.size() - 8);
                t = t.substr(0, (int)t.size() - 8);
                int shiftCounter = std::stoi(shift, 0, 2);
                t.erase((int)t.size() - shiftCounter);
                return decodeFromBinary(t);
            }
        } else {
            return s;
        }
    };
    
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int type;
        std::cin >> type;
        switch (type) {
            case 1: {
                int idx;
                std::cin >> idx;
                --idx;
                std::cout << table[idx] << "\n";
                break;
            }
            case 2: {
                int idx;
                std::cin >> idx;

                std::string key;
                if (idx == 0) {
                    std::cin >> key;
                    key = alter(key);
                } else {
                    --idx;
                    key = table[idx].first;
                }

                std::string value;
                std::cin >> value;
                value = alter(value);
                
                table.insert(key, value);
                std::cout << std::make_pair(key, value) << "\n";
                break;
            }
            case 3: {
                int idx;
                std::cin >> idx;

                std::string key;
                if (idx == 0) {
                    std::cin >> key;
                    key = alter(key);
                } else {
                    --idx;
                    key = table[idx].first;
                }

                std::string value;
                std::cin >> value;
                value = alter(value);
                
                std::cout << std::make_pair(key, value) << "\n";
                break;
            }
        }
    }
}