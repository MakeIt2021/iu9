#include <stdio.h>
#include <stdlib.h>

struct Elem {
    struct Elem *prev, *next;
    int v;
};

struct Elem *create_elem(int v) {
    struct Elem *new_elem = malloc(sizeof(struct Elem));
    
    new_elem->v = v;
    new_elem->prev = new_elem->next = NULL;
    return new_elem;
}

struct Elem *insert_end(struct Elem *head, struct Elem *new_elem) {
    if (head == NULL) {
        new_elem->next = new_elem->prev = new_elem;
        return new_elem;
    } else {
        struct Elem *tail = head->prev;

        tail->next = new_elem;
        new_elem->prev = tail;
        new_elem->next = head;
        head->prev = new_elem;

        return head;
    }
}

struct Elem *insertion_sort(struct Elem *head, int n) {
    if (head == NULL || n <= 1)
        return head;

    struct Elem *current = head->next;

    for (int i = 1; i < n; i++) {
        struct Elem *next = current->next;

        if (current->v < head->v) {
            current->prev->next = current->next;
            current->next->prev = current->prev;

            current->prev = head->prev;
            current->next = head;
            head->prev->next = current;
            head->prev = current;

            head = current;
        } else {
            struct Elem *j = head;
            while (j->next != head && j->next->v < current->v) {
                j = j->next;
            }

            if (j->next != current) {
                current->prev->next = current->next;
                current->next->prev = current->prev;

                current->prev = j;
                current->next = j->next;
                j->next->prev = current;
                j->next = current;

                if (j == head->prev) {
                    head->prev = current;
                }
            }
        }

        current = next;
    }

    return head;
}

void free_list(struct Elem *head, int n) {
    if (head == NULL)
        return;

    struct Elem *iter = head;
    for (int i = 0; i < n; i++) {
        struct Elem *temp = iter;
        iter = iter->next;
        free(temp);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    struct Elem *head = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);

        struct Elem *new_elem = create_elem(val);
        if (!new_elem) {
            free_list(head, i);
            return 1;
        }

        head = insert_end(head, new_elem);
    }

    head = insertion_sort(head, n);

    if (head == NULL)
        return 1;

    struct Elem *iter = head;
    for (int i = 0; i < n; i++) {
        printf("%d", iter->v);
        if (i < n - 1)
            printf(" ");
        iter = iter->next;
    }
    printf("\n");

    free_list(head, n);

    return 0;
}