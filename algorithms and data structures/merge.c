#include <stdio.h>
#include <stdlib.h>

void heapify(int *heap_values, int *heap_array_idx, int heap_size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap_values[left] < heap_values[smallest])
        smallest = left;

    if (right < heap_size && heap_values[right] < heap_values[smallest])
        smallest = right;

    if (smallest != i) {        
        int heap_values_i = heap_values[i];
        heap_values[i] = heap_values[smallest];
        heap_values[smallest] = heap_values_i;

        int heap_array_idx_i = heap_array_idx[i];
        heap_array_idx[i] = heap_array_idx[smallest];
        heap_array_idx[smallest] = heap_array_idx_i;


        heapify(heap_values, heap_array_idx, heap_size, smallest);
    }
}

void insert_heap(int *heap_values, int *heap_array_idx, int *heap_size, int value, int array_idx) {
    int i = (*heap_size)++;
    heap_values[i] = value;
    heap_array_idx[i] = array_idx;

    while (i > 0 && heap_values[(i - 1) / 2] > heap_values[i]) {
        int heap_values_i = heap_values[i];
        heap_values[i] = heap_values[(i - 1) / 2];
        heap_values[(i - 1) / 2] = heap_values_i;

        int heap_array_idx_i = heap_array_idx[i];
        heap_array_idx[i] = heap_array_idx[(i - 1) / 2];
        heap_array_idx[(i - 1) / 2] = heap_array_idx_i;
        
        i = (i - 1) / 2;
    }
}

void extract_min(int *heap_values, int *heap_array_idx, int *heap_size, int *min_value, int *min_array_idx) {
    *min_value = heap_values[0];
    *min_array_idx = heap_array_idx[0];
    heap_values[0] = heap_values[--(*heap_size)];
    heap_array_idx[0] = heap_array_idx[*heap_size];
    heapify(heap_values, heap_array_idx, *heap_size, 0);
}

int main() {
    int k;

    scanf("%d", &k);

    int *sizes = malloc(k * sizeof(int));
    int *base = malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        scanf("%d", &sizes[i]);
    }

    base[0] = 0;
    for (int i = 1; i < k; i++) {
        base[i] = base[i - 1] + sizes[i - 1];
    }

    int total_elements = base[k - 1] + sizes[k - 1];
    int *elements = malloc(total_elements * sizeof(int));

    for (int i = 0; i < total_elements; i++) {
        scanf("%d", &elements[i]);
    }

    int *heap_values = malloc(k * sizeof(int));
    int *heap_array_idx = malloc(k * sizeof(int));
    int *current_indices = malloc(k * sizeof(int));

    int heap_size = 0;
    for (int i = 0; i < k; i++) {
        current_indices[i] = 0;
        if (sizes[i] > 0) {
            insert_heap(heap_values, heap_array_idx, &heap_size, elements[base[i]], i);
        }
    }

    while (heap_size > 0) {
        int min_value, min_array_idx;

        extract_min(heap_values, heap_array_idx, &heap_size, &min_value, &min_array_idx);
        printf("%d ", min_value);

        if (++current_indices[min_array_idx] < sizes[min_array_idx]) {
            int next_value = elements[base[min_array_idx] + current_indices[min_array_idx]];
            insert_heap(heap_values, heap_array_idx, &heap_size, next_value, min_array_idx);
        }
    }

    printf("\n");

    free(sizes);
    free(base);
    free(elements);
    free(heap_values);
    free(heap_array_idx);
    free(current_indices);

    return 0;
}