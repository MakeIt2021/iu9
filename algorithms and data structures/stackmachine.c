#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { STACK_SIZE =200000 };

long long int stack[STACK_SIZE];
int top = -1;

void push(num)
{
    top++;
    stack[top] = num;
}

int pop()
{
    return stack[top--];
}

void processWord(char *words)
{
    char word[10];
    sscanf(words, "%s", word);

    if (strcmp(word, "CONST") == 0) {
        long long int num;
        sscanf(words + 6, "%lld", &num);
        push(num);
    } else if (strcmp(word, "ADD") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a + b);
    } else if (strcmp(word, "SUB") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a - b);
    } else if (strcmp(word, "MUL") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a * b);
    } else if (strcmp(word, "DIV") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a / b);
    } else if (strcmp(word, "MAX") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a > b ? a : b);
    } else if (strcmp(word, "MIN") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a < b ? a : b);
    } else if (strcmp(word, "NEG") == 0) {
        push(-pop());
    } else if (strcmp(word, "DUP") == 0) {
        long long int x = pop();
        push(x);
        push(x);
    } else if (strcmp(word, "SWAP") == 0) {
        long long int a = pop();
        long long int b = pop();
        push(a);
        push(b);
    } else if (strcmp(word, "END") == 0) {
        long long int res = pop();
        printf("%lld\n", res);
    }
}

int main()
{
    char word[100];

    while (fgets(word, sizeof(word), stdin)) {
        word[strcspn(word, "\n")] = 0;
        processWord(word);
    }

    return 0;
}
