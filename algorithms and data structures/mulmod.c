#include <stdio.h>

int main() {
    unsigned long long a, b, m;
    scanf("%llu %llu %llu", &a, &b, &m);

    unsigned long long result = 0;
    a = a % m;

    while (b > 0) {
        if (b & 1) {
            result = (result + a) % m;
        }

        a = (a * 2) % m;
        b >>= 1;
    }

    printf("%llu\n", result);
    return 0;
}