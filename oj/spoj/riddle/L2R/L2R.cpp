#include <stdio.h>
#include <math.h>

int main (void) {
    long long x;
    scanf ("%lld", &x);
    printf ("%lld\n", (long long) pow (x*32, 3));
    return 0;
}