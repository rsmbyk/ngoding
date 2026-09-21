#include <cstdio>
#include <cmath>

long long kamenetsky (long long n) {
    if (n < 0) return 0;
    if (n < 2) return 1;
    double k = (n * log10 (n/M_E)) + (log10 (2*M_PI*n) / 2.0);
    return (long long) floor (k) + 1;
}

int main (int argc, char const *argv[]) {
    long long tc, n;
    scanf ("%lld", &tc);
    
    while (tc--) {
        scanf ("%lld", &n);
        printf ("%lld\n", kamenetsky (n));
    }
    return 0;
}