#include <stdio.h>

int main() {
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5 - i; ++j) {
            printf("*");
        }
        if (i == 2) {
            printf("A\n");
        } else {
            printf("%d\n", i + 1);
        }
    }
    return 0;
}
