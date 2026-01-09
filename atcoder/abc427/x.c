#include <stdio.h>
#include <string.h>

int main() {
    char s[16];
    scanf("%s", s);

    int n = strlen(s);
    long long ans[364], l = 0;
    int pos[5];
    pos[0] = -1;
    pos[4] = n - 1;

    for (pos[1] = 0; pos[1] < n - 1; ++pos[1]) {
        for (pos[2] = pos[1] + 1; pos[2] < n - 1; ++pos[2]) {
            for (pos[3] = pos[2] + 1; pos[3] < n - 1; ++pos[3]) {
                long long sum = 0, cur = 0;

                for (int t = 1; t < 5; ++t) {
                    for (int p = pos[t - 1] + 1; p <= pos[t]; ++p) {
                        cur *= 10;
                        cur += s[p] - '0';
                    }
                    sum += cur;
                    cur = 0;
                }

                ans[l++] = sum;
            }
        }
    }

    for (int i = 0; i < l; ++i) {
        for (int j = i + 1; j < l; ++j) {
            if (ans[i] < ans[j]) {
                long long t = ans[i];
                ans[i] = ans[j];
                ans[j] = t;
            }
        }
    }

    for (int i = 0; i < l; ++i) {
        printf("%lld ", ans[i]);
    }
    printf("\n");

    return 0;
}