void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    if (nel < 2) {
        return;
    }

    unsigned long start = 0;
    unsigned long end = nel - 1;
    int swapped;

    do {
        swapped = 0;

        for (unsigned long i = start; i < end; i++) {
            if (compare(i, i + 1) > 0) {
                swap(i, i + 1);
                swapped = 1;
            }
        }
        if (!swapped) break;

        end--;

        for (unsigned long i = end; i > start; i--) {
            if (compare(i - 1, i) > 0) {
                swap(i - 1, i);
                swapped = 1;
            }
        }
        start++;

    } while (swapped);
}
