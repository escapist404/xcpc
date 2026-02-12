#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

const std::string s = "0112233445142015320125410214530214510214102302142025101203201451451522302514203214510021454101002532";
const int n = s.size();

int main() {
    int c = 0;
    for (int i = 0; i < n; ++i) {
        switch (s[i]) {
            case '0':
                switch (c) {
                    case 0:
                        c = 3;
                        break;
                    case 1:
                        c = 2;
                        break;
                    case 2:
                        c = 1;
                        break;
                    case 3:
                        c = 0;
                        break;
                }
                break;
            case '1':
                switch (c) {
                    case 0:
                        c = 0;
                        break;
                    case 1:
                        c = 3;
                        break;
                    case 2:
                        c = 2;
                        break;
                    case 3:
                        c = 1;
                        break;
                }
                break;
            case '2':
                switch (c) {
                    case 0:
                        c = 1;
                        break;
                    case 1:
                        c = 0;
                        break;
                    case 2:
                        c = 3;
                        break;
                    case 3:
                        c = 2;
                        break;
                }
                break;
            case '3':
                switch (c) {
                    case 0:
                        c = 2;
                        break;
                    case 1:
                        c = 1;
                        break;
                    case 2:
                        c = 0;
                        break;
                    case 3:
                        c = 3;
                        break;
                }
                break;
            case '4':
                switch (c) {
                    case 0:
                        c = 1;
                        break;
                    case 1:
                        c = 2;
                        break;
                    case 2:
                        c = 3;
                        break;
                    case 3:
                        c = 0;
                        break;
                }
                break;
            case '5':
                switch (c) {
                    case 0:
                        c = 3;
                        break;
                    case 1:
                        c = 0;
                        break;
                    case 2:
                        c = 1;
                        break;
                    case 3:
                        c = 2;
                        break;
                }
                break;
        }
        std::cout << c;
    }

    std::cout << "\n";

    return 0;
}
