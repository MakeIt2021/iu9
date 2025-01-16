#include <stdio.h>


void revarray(void *base, size_t nel, size_t width)
{
    char* first = (char*)base;
    char* last = (char*)base + (nel - 1) * width;


    for (int i = 0; i < nel / 2; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char temp = first[j];
            first[j] = last[j];
            last[j] = temp;
        }

        first += width;
        last -= width;
    }
    
}

void print_arr(double* base, size_t nel) {
    for (int i = 0; i < nel; i++)
    {
        printf("%lf ", base[i]);
    }
    printf("\n");
}


int main (int argc, char ** argv) {
    double arr[10];
    for (int i = 0; i < 10; i++)
    {
        scanf("%lf", &arr[i]);
    }
    
    print_arr(arr, 10);
    revarray(arr, 10, 8);
    print_arr(arr, 10);
}