#include <stdio.h>
int main() {
    typedef struct {
        union {
            unsigned int i;
            float d;
        } u;
    } Number;

    Number n;
    n.u.d = 82.6;
    printf("%u\n", n.u.i);
    return 0;
}
