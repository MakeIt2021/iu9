#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int buffSize;
    int head;
    int tail;
    int queueSize;
} Queue;

void initQueue(Queue* q)
{
    q->buffSize = 4;
    q->data = malloc(sizeof(int) * q->buffSize);
    q->head = 0;
    q->tail = 0;
    q->queueSize = 0;
}

int queueEmpty(Queue* q) {
    return q->queueSize == 0;
}

void doubleSize(Queue* q)
{
    int newBuffSize = q->buffSize * 2;
    int* newData = malloc(sizeof(int) * newBuffSize);

    for (int i = 0; i < q->queueSize; i++) {
        newData[i] = q->data[(q->head + i) % q->buffSize];
    }

    free(q->data);
    q->data = newData;
    q->buffSize = newBuffSize;
    q->head = 0;
    q->tail = q->queueSize;
}

void enqueue(Queue* q, int el)
{
    if(q->queueSize == q->buffSize) {
        doubleSize(q);
    }

    q->data[q->tail] = el;
    q->tail = (q->tail + 1) % q->buffSize;
    q->queueSize++;
}

int dequeue(Queue* q)
{
    int deleted = q->data[q->head];
    q->head = (q->head + 1) % q->buffSize;
    q->queueSize--;

    return deleted;
}

void processWord(Queue* q, char* words)
{
    if (strncmp(words, "ENQ", 3) == 0) {
        int x;
        sscanf(words + 4, "%d", &x);
        enqueue(q, x);
    } else if (strcmp(words, "DEQ") == 0) {
        printf("%d\n", dequeue(q));
    } else if (strcmp(words, "EMPTY") == 0) {
        printf("%s\n", queueEmpty(q) ? "true" : "false");
    } else if (strcmp(words, "END") == 0) {
        free(q->data);
        return;
    }
}

int main()
{
    Queue q;
    initQueue(&q);

    char words[100];
    while (fgets(words, sizeof(words), stdin)) {
        words[strcspn(words, "\n")] = 0;
        processWord(&q, words);
    }

    return 0;
}
