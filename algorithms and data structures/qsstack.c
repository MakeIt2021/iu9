#include <stdio.h>
#include <stdlib.h>


struct Task {
    int low, high;
};

enum { STACK_SIZE = 1000 };
struct Task stack[STACK_SIZE];
int top = -1;

void push(int low, int high)
{
    stack[top + 1] = (struct Task) {low, high};
    top++;
}

struct Task pop()
{
    return stack[top--];
}

int partition_arr(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;

            int arr_i = arr[i];
            arr[i] = arr[j];
            arr[j] = arr_i;
        }
    }

    int arr_ip1 = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = arr_ip1;

    return i + 1;
}

void quicksort(int arr[], int n) {
    push(0, n - 1);

    while (top != -1) {
        struct Task current = pop();
        int low = current.low;
        int high = current.high;

        if (low < high) {
            int pivotInd = partition_arr(arr, low, high);

            if (pivotInd - 1 > low) {
                push(low, pivotInd - 1);
            }
            if (pivotInd + 1 < high) {
                push(pivotInd + 1, high);
            }
        }
    }
}

int main()
{
    int nel;
    scanf("%d", &nel);

    int* arr = malloc(sizeof(int) * nel);
    for (int i = 0; i < nel; i++) {
        scanf("%d", &arr[i]);
    }

    quicksort(arr, nel);

    for (int i = 0; i < nel; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");

    free(arr);

    return 0;
}
