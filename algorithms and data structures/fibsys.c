#include <stdio.h>
#include <stdlib.h>

#define MAX_FIBS 93


void generate_fibs(unsigned long long fibs[], int *count) {
    fibs[0] = 1;
    fibs[1] = 2;
    *count = 2;
    while (fibs[*count - 1] <= (1ULL << 63)) {
        fibs[*count] = fibs[*count - 1] + fibs[*count - 2];
        (*count)++;
    }
}


void fibsys(unsigned long long x, unsigned long long fibs[], int count) {
    if (x == 0) {
        printf("0\n");
        return;
    }
    
    char result[MAX_FIBS] = {0};
    int i;

    for (i = count - 1; i >= 0 && x > 0; i--) {
        if (fibs[i] <= x) {
            result[i] = 1;
            x -= fibs[i];
        }
    }

    int leading_zero = 1;
    for (i = count - 1; i >= 0; i--) {
        if (result[i] == 1) {
            leading_zero = 0;
        }
        if (!leading_zero) {
            printf("%d", result[i]);
        }
    }
    printf("\n");
}

int main() {
    unsigned long long x;
    unsigned long long fibs[MAX_FIBS];
    int count;

    generate_fibs(fibs, &count);

    scanf("%llu", &x);

    fibsys(x, fibs, count);

    return 0;
}
