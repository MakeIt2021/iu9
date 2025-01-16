#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = new_node->prev = NULL;
    return new_node;
}

void append_node(Node** head_ref, Node** tail_ref, Node* node) {
    if (*head_ref == NULL) {
        *head_ref = *tail_ref = node;
        node->next = node->prev = node;
    } else {
        node->prev = *tail_ref;
        node->next = *head_ref;
        (*tail_ref)->next = node;
        (*head_ref)->prev = node;
        *tail_ref = node;
    }
}

void print_list(Node* head) {
    if (head == NULL) return;
    Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

void free_list(Node* head) {
    if (head == NULL) return;
    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(head);
}

void break_circular(Node* head, Node** head_ref, Node** tail_ref) {
    if (head == NULL) {
        *head_ref = *tail_ref = NULL;
        return;
    }
    *head_ref = head;
    *tail_ref = head->prev;
    (*tail_ref)->next = NULL;
    (*head_ref)->prev = NULL;
}

void make_circular(Node* head, Node* tail) {
    if (head == NULL || tail == NULL) return;
    head->prev = tail;
    tail->next = head;
}

Node* get_tail(Node* head) {
    if (head == NULL) return NULL;
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

void concatenate_lists(Node* less_head, Node* equal_head, Node* greater_head, Node** new_head, Node** new_tail) {
    *new_head = *new_tail = NULL;

    if (less_head != NULL) {
        *new_head = less_head;
        *new_tail = get_tail(less_head);
    }

    if (equal_head != NULL) {
        if (*new_head == NULL) {
            *new_head = equal_head;
            *new_tail = get_tail(equal_head);
        } else {
            (*new_tail)->next = equal_head;
            equal_head->prev = *new_tail;
            *new_tail = get_tail(equal_head);
        }
    }

    if (greater_head != NULL) {
        if (*new_head == NULL) {
            *new_head = greater_head;
            *new_tail = get_tail(greater_head);
        } else {
            (*new_tail)->next = greater_head;
            greater_head->prev = *new_tail;
            *new_tail = get_tail(greater_head);
        }
    }
}

void quicksort(Node* head, Node** sorted_head, Node** sorted_tail) {
    if (head == NULL || head->next == NULL) {
        *sorted_head = head;
        *sorted_tail = head;
        return;
    }

    int pivot = abs(head->data);

    Node* less_head = NULL;
    Node* less_tail = NULL;
    Node* equal_head = NULL;
    Node* equal_tail = NULL;
    Node* greater_head = NULL;
    Node* greater_tail = NULL;

    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        current->next = current->prev = NULL;
        int abs_val = abs(current->data);
        if (abs_val < pivot) {
            if (less_head == NULL) {
                less_head = less_tail = current;
            } else {
                less_tail->next = current;
                current->prev = less_tail;
                less_tail = current;
            }
        } else if (abs_val == pivot) {
            if (equal_head == NULL) {
                equal_head = equal_tail = current;
            } else {
                equal_tail->next = current;
                current->prev = equal_tail;
                equal_tail = current;
            }
        } else {
            if (greater_head == NULL) {
                greater_head = greater_tail = current;
            } else {
                greater_tail->next = current;
                current->prev = greater_tail;
                greater_tail = current;
            }
        }

        current = next_node;
    }

    Node* sorted_less_head = NULL;
    Node* sorted_less_tail = NULL;
    quicksort(less_head, &sorted_less_head, &sorted_less_tail);

    Node* sorted_greater_head = NULL;
    Node* sorted_greater_tail = NULL;
    quicksort(greater_head, &sorted_greater_head, &sorted_greater_tail);

    concatenate_lists(sorted_less_head, equal_head, sorted_greater_head, sorted_head, sorted_tail);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
        int value;
        if (scanf("%d", &value) != 1) {
            free_list(head);
            return EXIT_FAILURE;
        }
        Node* new_node = create_node(value);
        append_node(&head, &tail, new_node);
    }

    Node* linear_head = NULL;
    Node* linear_tail = NULL;
    break_circular(head, &linear_head, &linear_tail);

    Node* sorted_head = NULL;
    Node* sorted_tail = NULL;
    quicksort(linear_head, &sorted_head, &sorted_tail);

    make_circular(sorted_head, sorted_tail);

    print_list(sorted_head);

    free_list(sorted_head);

    return 0;
}
