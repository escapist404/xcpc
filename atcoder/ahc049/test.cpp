#include <vector>
#include <list>
#include <iostream>

struct Type {
    int value;
    Type(const int v = 0) : value(v) {}
};

int main() {
    std::list<Type*> con;
    for (int i = 0; i < 5; ++i) {
        con.push_back(new Type(i));
    }

    for (auto it = con.rbegin(); it != con.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    for (auto it = con.rbegin(); it != con.rend(); ++it) {
        std::cout << (*it)->value << " ";
    }
    std::cout << "\n";
}