#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dsort(char* str)
{
    if (str == NULL) {
        return;
    }
    int len = strlen(str);

    int cnt[26] = {0};
    for (int i = 0; i < len; i++) {
        cnt[str[i] - 'a']++;
    }

    for (int i = 0, j = 0; i < 26; i++) {
        while (cnt[i]) {
            str[j] = 'a' + i;
            j++;

            cnt[i]--;
        }
    }
}

int main()
{
    int n = 1000001;
    char* arr = malloc(sizeof(char) * (n + 1));

    fgets(arr, n + 1, stdin);
    arr[strlen(arr) - 1] = 0;
    
    dsort(arr);

    printf("%s\n", arr);

    free(arr);

    return 0;
}