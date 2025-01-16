#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void remove_leading_zeros(char *s) {
    int i = 0;
    while (s[i] == '0' && s[i+1] != '\0') i++;
    if (i > 0) memmove(s, s+i, strlen(s+i)+1);
}

int compare(const char *a, const char *b) {
    char a_copy[1024];
    char b_copy[1024];
    strcpy(a_copy, a);
    strcpy(b_copy, b);
    remove_leading_zeros(a_copy);
    remove_leading_zeros(b_copy);
    
    int len_a = strlen(a_copy);
    int len_b = strlen(b_copy);
    if (len_a > len_b) {
        return 1;
    }
    if (len_a < len_b) return -1;
    for (int i = 0; i < len_a; i++) {
        if (a_copy[i] > b_copy[i]) {
            return 1;
        }

        if (a_copy[i] < b_copy[i]) {
            return -1;
        }
         
    }
    return 0;
}

void subtract(char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    char result[len_a + 1];
    result[len_a] = '\0';
    int carry = 0;
    for (int i = 0; i < len_a; i++) {
        int bit_a = a[len_a - 1 - i] - '0';
        int bit_b = (i < len_b) ? (b[len_b - 1 - i] - '0') : 0;
        int diff = bit_a - bit_b - carry;
        if (diff < 0) {
            diff += 2;
            carry = 1;
        }
        else {
            carry = 0;
        }
        result[len_a - 1 - i] = diff + '0';
    }
    int start = 0;
    while (start < len_a -1 && result[start] == '0') start++;
    memmove(a, result + start, len_a - start +1);
}

void divide_by_two(char *a) {
    int len = strlen(a);
    if (len == 1) {
        a[0] = '0';
        a[1] = '\0';
        return;
    }
    a[len -1] = '\0';
}

int is_even(const char *a) {
    return a[strlen(a)-1] == '0';
}

int is_zero(const char *a) {
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] != '0') return 0;
    }
    return 1;
}

void copy_string(char *dest, const char *src) {
    strcpy(dest, src);
}

int is_binary(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '0' && s[i] != '1') return 0;
    }
    return 1;
}

void multiply_by_power_of_two(char *a, int k) {
    for (int i = 0; i < k; i++) {
        size_t len = strlen(a);
        if (len +1 >= 1024) {
            exit(1);
        }
        a[len] = '0';
        a[len+1] = '\0';
    }
}

void binary_gcd(char *a, char *b, char *result) {
    remove_leading_zeros(a);
    remove_leading_zeros(b);
    
    if (is_zero(a)) {
        strcpy(result, b);
        return;
    }
    if (is_zero(b)) {
        strcpy(result, a);
        return;
    }
    
    int k = 0;
    
    while (!is_zero(a) && !is_zero(b)) {
        if (is_even(a) && is_even(b)) {
            k++;
            divide_by_two(a);
            divide_by_two(b);
        }
        else if (is_even(a)) {
            divide_by_two(a);
        }
        else if (is_even(b)) {
            divide_by_two(b);
        }
        else {
            if (compare(a, b) >=0) {
                subtract(a, b);
                divide_by_two(a);
            }
            else {
                subtract(b, a);
                divide_by_two(b);
            }
        }
    }
    
    if (is_zero(a)) {
        strcpy(result, b);
    }
    else {
        strcpy(result, a);
    }
    
    multiply_by_power_of_two(result, k);
}

int main(int argc, char *argv[]) {
    char a[1024];
    char b[1024];
    strncpy(a, argv[1], 1023);
    a[1023] = '\0';
    strncpy(b, argv[2], 1023);
    b[1023] = '\0';
    remove_leading_zeros(a);
    remove_leading_zeros(b);

    char result[2048] = "";

    binary_gcd(a, b, result);

    printf("%s\n", result);
    return 0;
}
