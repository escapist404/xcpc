#include <bits/stdc++.h>

using i128 = __int128;
using u128 = unsigned __int128;
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned int;

std::string numberExpr2Name(u128 expr) {
    auto map = [](int v) -> char{
        if (v == 0) {
            return ' ';
        } else if (v <= 10) {
            return '0' + (v - 1);
        } else if (v <= 36) {
            return 'A' + (v - 11);
        } else {
            return '_';
        }
    };
    std::string name;
    for (int i = 0; i < 11; ++i) {
        int v = expr % 38;
        name.push_back(map(v));
        expr /= 38;
    }
    std::reverse(name.begin(), name.end());
    while (name.back() == ' ') {
        name.pop_back();
    }
    return name;
}

u128 name2numberExpr(std::string name) {
    auto map = [](char ch) {
        if (ch == ' ') {
            return 0;
        } else if (0 <= ch && ch <= '9') {
            return ch - '0' + 1;
        } else if ('A' <= ch && ch <= 'Z') {
            return ch - 'A' + 11;
        } else {
            return 37;
        }
    };

    while (name.size() < 11) {
        name.push_back(' ');
    }

    u128 expr = 0;
    for (auto ch : name) {
        expr *= 38;
        expr += map(ch);
    }

    return expr;
}

std::string shortNumberExpr2Name(u128 expr) {
    std::string name("------");
    name[5] = 'A' + expr % 26;
    expr /= 26;
    name[4] = 'A' + expr % 26;
    expr /= 26;
    name[3] = 'A' + expr % 26;
    expr /= 26;
    name[2] = '0' + expr % 10;
    expr /= 10;
    if (expr % 36 <= 9) {
        name[1] = '0' + expr % 36;
    } else {
        name[1] = 'A' + (expr % 36 - 10);
    }
    expr /= 36;
    if (expr == 0) {
        name[0] = ' ';
    } else if (expr <= 10) {
        name[0] = '0' + (expr - 1);
    } else {
        name[0] = 'A' + (expr - 11);
    }

    if (name[0] == ' ') {
        name.erase(name.begin());
    }

    return name;
}

u128 name2ShortNumberExpr(std::string name) {
    if (name.size() == 5) {
        name.insert(name.begin(), ' ');
    }

    u128 expr = 0;
    
    if ('0' <= name[0] && name[0] <= '9') {
        expr += 1LL * (name[0] - '0' + 1) * 36 * 10 * 26 * 26 * 26;
    } else if ('A' <= name[0] && name[0] <= 'Z') {
        expr += 1LL * (name[0] - 'A' + 11) * 36 * 10 * 26 * 26 * 26;
    }

    if ('0' <= name[1] && name[1] <= '9') {
        expr += 1LL * (name[1] - '0') * 10 * 26 * 26 * 26;
    } else if ('A' <= name[1] && name[1] <= 'Z') {
        expr += 1LL * (name[1] - 'A' + 10) * 10 * 26 * 26 * 26;
    }

    expr += 1LL * (name[2] - '0') * 26 * 26 * 26;
    expr += 1LL * (name[3] - 'A') * 26 * 26;
    expr += 1LL * (name[4] - 'A') * 26;
    expr += 1LL * (name[5] - 'A');

    return expr;
}

const u64 OFFSET = 47'055'833'459ULL;
const u64 MASK = std::numeric_limits<u64>::max();

u128 hashValue(u128 expr, int len) {
    return expr * OFFSET >> (64 - len) & ((1LL << len) - 1);
}

std::ostream& operator<<(std::ostream& os, u128 v) {
    std::string s;
    while (v > 0) {
        s.push_back('0' + v % 10);
        v /= 10;
    }
    std::reverse(s.begin(), s.end());
    os << s;
    return os;
}

template <typename T>
T str2int(const std::string& str) {
    T val = 0;
    for (auto ch : str) {
        val <<= 1;
        val += ch - '0';
    }

    return val;
}

int main() {
    std::cerr << name2numberExpr("___________") << "\n";

    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::map<u128, std::string> dict12, dict25;

    while (n--) {
        std::string msg;
        std::cin >> msg;

        if (msg[0] == '1') {
            u128 id = str2int<u128>(msg.substr(1, 58));
            u32 hash = str2int<u32>(msg.substr(59, 12));

            std::string idName = numberExpr2Name(id);
            std::string hashName = "###";
            if (dict12.count(hash)) {
                hashName = "#" + dict12[hash];
            }
            
            if (msg.back() == '0') {
                std::cout << hashName << " " << idName << "\n";
            } else {
                std::cout << idName << " " << hashName << "\n";
            }

            dict25[hashValue(id, 25)] = idName;
            dict12[hashValue(id, 12)] = idName;
        } else {
            u32 receiver = str2int<u32>(msg.substr(1, 28));
            u32 sender = str2int<u32>(msg.substr(29, 28));
            u32 location = str2int<u32>(msg.substr(57, 15));

            bool dictChg[] = {false, false};

            if (receiver < (1 << 25)) {
                if (dict25.count(receiver)) {
                    std::cout << "#" << dict25[receiver];
                } else {
                    std::cout << "###";
                }
            } else {
                dictChg[0] = true;
                receiver -= (1 << 25);
                std::string name = shortNumberExpr2Name(receiver);
                std::cout << name;
            }

            std::cout << " ";

            if (sender < (1 << 25)) {
                if (dict25.count(sender)) {
                    std::cout << "#" << dict25[sender];
                } else {
                    std::cout << "###";
                }
            } else {
                dictChg[1] = true;
                sender -= (1 << 25);
                std::string name = shortNumberExpr2Name(sender);
                std::cout << name;
            }

            if (location > 0) {
                std::cout << " " << location;
            }
            std::cout << "\n";

            if (dictChg[0]) {
                std::string name = shortNumberExpr2Name(receiver);
                dict25[hashValue(name2numberExpr(name), 25)] = name;
                dict12[hashValue(name2numberExpr(name), 12)] = name;
            }

            if (dictChg[1]) {
                std::string name = shortNumberExpr2Name(sender);
                dict25[hashValue(name2numberExpr(name), 25)] = name;
                dict12[hashValue(name2numberExpr(name), 12)] = name;
            }
        }
    }

    return 0;
}
