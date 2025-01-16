#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix(const char *s, int *pi, int n) {
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        return 1;
    }

    const char *s = argv[1];
    int n = strlen(s);

    int *pi = (int *)malloc(n * sizeof(int));
    if (!pi) {
        return 1;
    }

    prefix(s, pi, n);

    for (int i = 1; i <= n; i++) {
        int period = i - pi[i - 1];
        if (i % period == 0) {
            int k = i / period;
            if (k > 1) {
                printf("%d %d\n", i, k);
            }
        }
    }

    free(pi);
    return 0;
}

