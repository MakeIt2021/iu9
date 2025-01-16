#include <stdio.h>


int main (int argc, char ** argv)
{
    int n, k;

    scanf("%d", &n);

    long long int arr[1000000];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    scanf("%d", &k);

    long long int cur_sum = 0;

    for (int i = 0; i < k; i++)
    {
        cur_sum += arr[i];
    }

    if (k == n)
    {
        printf("%lld\n", cur_sum);
        return 0;
    }
    
    int left = 0;
    long long int max_sum = cur_sum;

    for (int right = left + k; right < n; right++)
    {
        cur_sum = cur_sum + arr[right] - arr[left++];
        if (cur_sum > max_sum)
            max_sum = cur_sum;
    }

    printf("%lld\n", max_sum);
    

    return 0;
}