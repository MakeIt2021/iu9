#include <stdio.h>
#include <stdlib.h>

void heapify(int *heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        int heap_i = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = heap_i;

        heapify(heap, size, smallest);
    }
}

int extract_min(int *heap, int *size) {
    int min = heap[0];
    *size -= 1;
    heap[0] = heap[*size];
    heapify(heap, *size, 0);
    return min;
}

void insert_heap(int *heap, int *size, int value) {
    int i = *size;
    *size += 1;
    heap[i] = value;

    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        int heap_i = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = heap_i;
        i = (i - 1) / 2;
    }
}

int main() {
    int n; // nodes
    scanf("%d", &n);

    int m; // tasks
    scanf("%d", &m);

    int *heap = (int *)malloc(sizeof(int) * n);
    int heap_size = 0;

    for (int i = 0; i < n; i++) {
        insert_heap(heap, &heap_size, 0);
    }

    int t1, t2;
    int result = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &t1, &t2);

        int finish_time = extract_min(heap, &heap_size);
        int start_time = (t1 > finish_time) ? t1 : finish_time;
        int end_time = start_time + t2;

        if (end_time > result) {
            result = end_time;
        }

        insert_heap(heap, &heap_size, end_time);
    }

    printf("%d\n", result);
    free(heap);
    return 0;
}