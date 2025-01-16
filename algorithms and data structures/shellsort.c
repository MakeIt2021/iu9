#include <stdio.h>
#include <stdlib.h>

unsigned long fib_seq(int nel, unsigned long** p_a)
{
    unsigned long* fib = malloc(sizeof(unsigned long) * nel);

    if (fib == NULL) {
        return 0;
    }

    unsigned long a = 1;
    unsigned long b = 1;
    unsigned long next = 0;

    unsigned long count = 0;

    while (b < nel)
    {
        fib[count] = b;
        next = a + b;
        a = b;
        b = next;
        count++; 
    }

    for (unsigned long i = 0; i < count / 2; i++)
    {
        unsigned int t = fib[i];
        fib[i] = fib[count - i - 1];
        fib[count - i - 1] = t;
    }

    *p_a = fib;
    return count;
}

void shellsort(
    unsigned long nel,
    int (*compare)(unsigned long i, unsigned long j),
    void (*swap)(unsigned long i, unsigned long j)
)
{
    if (nel == 0) {
        return;
    }

    unsigned long* fib = NULL;
    unsigned long size = fib_seq(nel, &fib);

    if (fib == NULL)
    {
        return;
    }

    for (unsigned long i = 0; i < size; i++)
    {
        unsigned long d = fib[i];

        for (unsigned long j = d; j < nel; j++)
        {
            unsigned long p = j;

            while (p >= d && compare(p - d, p) > 0)
            {
                swap(p, p - d);
                p -= d;
            }
        }
    }

    free(fib);
}