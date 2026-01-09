#include <stdio.h>
#include <assert.h>
#include <string.h>

char s[1001];

int main() {
    int n = 0;
    while (1) {
        s[n] = getchar();
        if (s[n] == '\n' || s[n] == '\r') {
            break;
        }
        n++;
    }

    int ok = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] != s[n - 1 - i]) {
            ok = 0;
        }
    }

    if (ok == 1) {
        puts("Yes");
    } else {
        puts("No");
    }

    return 0;
}