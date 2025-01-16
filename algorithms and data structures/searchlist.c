#include "elem.h"
#include <stdio.h>

struct Elem* searchlist(struct Elem *list, int k)
{
    if (!list) {
        return NULL;
    }

    struct Elem* current = list;

    while (current) {
        if (current->tag == INTEGER) {
            if (current->value.i == k) {
                return current;
            }
        } 
        current = current->tail;
    }

    return NULL;
}
