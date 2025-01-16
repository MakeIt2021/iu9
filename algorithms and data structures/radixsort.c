#include <stdio.h>
#include <stdlib.h>

typedef union {
    int x;
    unsigned char bytes[4];
} Int32;

void countSort(Int32 *arr, int nel, int e)
{
    Int32* output = malloc(sizeof(Int32) * nel);
    int count[256] = {0};

    for (int i = 0; i < nel; i++) {
        count[arr[i].bytes[e]]++;
    }

    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    for (int i = nel - 1; i >= 0; i--) {
        output[count[arr[i].bytes[e]] - 1] = arr[i];
        count[arr[i].bytes[e]]--;
    }

    for (int i = 0; i < nel; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void negToFront(Int32 *arr, int nel) {
    Int32* output = malloc(sizeof(Int32) * nel);
    int index = 0;

    for (int i = 0; i < nel; i++) {
        if (arr[i].x < 0) {
            output[index++] = arr[i];
        }
    }

    for (int i = 0; i < nel; i++) {
        if (arr[i].x >= 0) {
            output[index++] = arr[i];
        }
    }

    for (int i = 0; i < nel; i++) {
        arr[i] = output[i];
    }

    free(output);
}

int main(int argc, char ** argv) {
    int n;
    scanf("%d", &n);

    Int32* arr = malloc(sizeof(Int32) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].x);
    }

    for (int e = 0; e < 4; e++) {
        countSort(arr, n, e);
    }

    negToFront(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i].x);
    }
    printf("\n");

    free(arr);
    return 0;
}
