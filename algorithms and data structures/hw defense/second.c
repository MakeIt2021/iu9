#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    int rankFirst;
    int rankSecond;
} Suffix;

static int cmp_suffix(const void *a, const void *b) {
    const Suffix *sa = (const Suffix *)a;
    const Suffix *sb = (const Suffix *)b;
    if (sa->rankFirst != sb->rankFirst) {
        return (sa->rankFirst < sb->rankFirst) ? -1 : 1;
    }
    if (sa->rankSecond != sb->rankSecond) {
        return (sa->rankSecond < sb->rankSecond) ? -1 : 1;
    }
    return 0;
}

int* build_suffix_array(const char *T) {
    int n = strlen(T);
    int *suffix_array = (int *)malloc(n * sizeof(int));

    int *rank = (int *)malloc(n * sizeof(int));
    int *rank_copy = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        rank[i] = (unsigned char)T[i];
    }

    Suffix *suffixes = (Suffix *)malloc(n * sizeof(Suffix));

    for (int i = 0; i < n; i++) {
        suffixes[i].index      = i;
        suffixes[i].rankFirst  = rank[i];
        suffixes[i].rankSecond = (i + 1 < n) ? rank[i + 1] : -1;
    }

    
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i++) {
            suffixes[i].index      = i;
            suffixes[i].rankFirst  = rank[i];
            suffixes[i].rankSecond = (i + k < n) ? rank[i + k] : -1;
        }

        qsort(suffixes, n, sizeof(Suffix), cmp_suffix);

        rank_copy[suffixes[0].index] = 0;
        for (int i = 1; i < n; i++) {
            if (suffixes[i].rankFirst == suffixes[i - 1].rankFirst &&
                suffixes[i].rankSecond == suffixes[i - 1].rankSecond) 
            {
                rank_copy[suffixes[i].index] = rank_copy[suffixes[i - 1].index];
            } else {
                rank_copy[suffixes[i].index] = rank_copy[suffixes[i - 1].index] + 1;
            }
        }

        for (int i = 0; i < n; i++) {
            rank[i] = rank_copy[i];
        }

        if (rank[suffixes[n - 1].index] == n - 1) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        suffix_array[i] = suffixes[i].index;
    }

    free(suffixes);
    free(rank);
    free(rank_copy);
    return suffix_array;
}

int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;
}

int lower_bound(const char *T, const char *S, const int *suffix_array, int n) {
    int left = 0, right = n;
    int lenS = strlen(S);

    while (left < right) {
        int mid = (left + right) / 2;
        if (strncmp(T + suffix_array[mid], S, lenS) < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int upper_bound(const char *T, const char *S, const int *suffix_array, int n) {
    int left = 0, right = n;
    int lenS = strlen(S);

    while (left < right) {
        int mid = (left + right) / 2;
        if (strncmp(T + suffix_array[mid], S, lenS) <= 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int main(int argc, char **argv) {
    const char *S = argv[1];
    const char *T = argv[2];

    int n = strlen(T);
    if (n == 0) {
        printf("\n");
        return 0;
    }

    int *suffix_array = build_suffix_array(T);

    int lower = lower_bound(T, S, suffix_array, n);
    int upper = upper_bound(T, S, suffix_array, n);

    int count = upper - lower;
    if (count <= 0) {
        printf("\n");
        free(suffix_array);
        return 0;
    }

    int *matches = (int *)malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        matches[i] = suffix_array[lower + i];
    }

    qsort(matches, count, sizeof(int), compare_ints);

    for (int i = 0; i < count; i++) {
        printf("%d ", matches[i]);
    }
    printf("\n");

    free(matches);
    free(suffix_array);

    return 0;
}
