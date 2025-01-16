#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void frame(int h, int w, const char *str) {
    long str_len = strlen(str);
    if (w - 2 < str_len || h < 3) {
        printf("Error\n");
        return;
    }

    for (int i = 0; i < w; i++) {
        printf("*");
    }
    printf("\n");

    int half_top = (h - 3) / 2;
    int half_bottom = (h - 3) - half_top;

    for (int i = 0; i < half_top; i++) {
        printf("*");
        for (int j = 0; j < w - 2; j++) {
            printf(" ");
        }
        printf("*\n");
    }

    int half_left = ((w - 2) - str_len) / 2;
    int half_right = (w - 2) - str_len - half_left;


    printf("*");
    
    for (int i = 0; i < half_left; i++) {
        printf(" ");
    }

    printf("%s", str);

    for (int i = 0; i < half_right; i++) {
        printf(" ");
    }
    printf("*\n");

    for (int i = 0; i < half_bottom; i++) {
        printf("*");
        for (int j = 0; j < w - 2; j++) {
            printf(" ");
        }
        printf("*\n");
    }

    for (int i = 0; i < w; i++) {
        printf("*");
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: frame <height> <width> <text>\n");
        return 0;
    }

    frame(atoi(argv[1]), atoi(argv[2]), argv[3]);

    return 0;
}