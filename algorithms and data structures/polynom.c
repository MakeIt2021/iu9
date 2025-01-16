#include <stdio.h>


int main (int argc, char ** argv)
{
    int n;
    long long int x0;
    scanf("%d %lld", &n, &x0);

    long long int coefs[n + 1];

    for (int i = 0; i <= n; i++) {
        scanf("%lld", &coefs[i]);
    }

    long long int Pn = coefs[0];
    long long int Pn_prime = n * coefs[0];
    int prime_extra_coef = n;

    for (int i = 1; i <= n; i++) {
        Pn = Pn * x0 + coefs[i];
        if (i < n)
            Pn_prime = Pn_prime * x0 + (--prime_extra_coef) * coefs[i];
    }

    printf("%lld %lld\n", Pn, Pn_prime);
    return 0;
}