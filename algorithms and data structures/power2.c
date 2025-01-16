#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    int res = 0;
    int n;

    scanf("%d", &n);

    int arr[24];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    
    for (int mask = 1; mask < (1 << n); mask++) {
        int sum = 0;

        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                sum += arr[j];
            }
        }
        
        if (sum > 0 && (sum & (sum - 1)) == 0) {
            res++;
        }
    }

    printf("%d\n", res);
    return 0;
}