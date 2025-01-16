#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Day, Month, Year;
} Date;

void countSort(Date* arr, int nel, int e, int base)
{
    Date* output = malloc(sizeof(Date) * nel);
    int* count  = malloc(sizeof(int) * (base + 1));

    for (int i = 0; i <= base; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < nel; i++) {
        int digit;
        if (e == 0) {
            digit = arr[i].Day;
        } else if (e == 1) {
            digit = arr[i].Month;
        } else {
            digit = arr[i].Year;
        }
        count[digit]++;
    }


    for (int i = 1; i <= base; i++) {
        count[i] += count[i - 1];
    }

    for (int i = nel - 1; i >= 0; i--) {
        int digit;
        if (e == 0) {
            digit = arr[i].Day;
        } else if (e == 1) {
            digit = arr[i].Month;
        } else {
            digit = arr[i].Year;
        }
        output[count[digit] - 1] = arr[i]; 
        count[digit]--;
    }

    for (int i = 0; i < nel; i++) {
        arr[i] = output[i];
    }

    free(output);
    free(count);
}

int main(int argc, char ** argv) {
    int n;
    scanf("%d", &n);

    Date* d = malloc(sizeof(Date) * n);
    if (!d) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d %d %d", &d[i].Year, &d[i].Month, &d[i].Day) != 3 ||
         d[i].Year < 1970 || d[i].Year > 2030 ||
         d[i].Month < 1 || d[i].Month > 12 ||
         d[i].Day < 1 || d[i].Day > 31) {
            free(d);
            return 1;
        }
    }

    countSort(d, n, 0, 31);
    countSort(d, n, 1, 12);
    countSort(d, n, 2, 2030);

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%04d %02d %02d\n", d[i].Year, d[i].Month, d[i].Day);
    }
 
    free(d);
    return 0;
}