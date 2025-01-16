#include <stdio.h>

int main() {
    int size_a, size_b;
    unsigned int a = 0, b = 0;

    scanf("%d", &size_a);
    for (int i = 0; i < size_a; i++) {
        int element;
        scanf("%d", &element);
        a |= (1 << element);
    }

    scanf("%d", &size_b);
    for (int i = 0; i < size_b; i++) {
        int element;
        scanf("%d", &element);
        b |= (1 << element);
    }

    unsigned int intersection = a & b;

    for (int i = 0; i < 32; i++) {
        if (intersection & (1 << i)) {
            printf("%d ", i);
        }
    }

    printf("\n");
    return 0;
}