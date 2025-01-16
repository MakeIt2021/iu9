#include <stdio.h>
#include <stdlib.h>

int compare_ll(const void* a, const void* b) {
    long long arg1 = *(const long long*)a;
    long long arg2 = *(const long long*)b;
    if (arg1 < arg2) 
        return -1;
    if (arg1 > arg2) 
        return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    int* a = malloc(n * sizeof(int));

    long long* prefix_xor = malloc((n + 1) * sizeof(long long));

    prefix_xor[0] = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        prefix_xor[i + 1] = prefix_xor[i] ^ ((long long)a[i]);
    }

    qsort(prefix_xor, n + 1, sizeof(long long), compare_ll);

    long long total = 0;
    int current_count = 1;
    for (int i = 1; i <= n; i++) {
        if (prefix_xor[i] == prefix_xor[i - 1]) {
            current_count++;
        } else {
            total += ((long long)current_count * (current_count - 1)) / 2;
            current_count = 1;
        }
    }

    total += ((long long)current_count * (current_count - 1)) / 2;

    printf("%lld\n", total);

    free(a);
    free(prefix_xor);

    return 0;
}
