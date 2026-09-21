#include <cstdio>

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        unsigned long long n, r=0;
        scanf ("%llu", &n);
        
        while (n > 1) {
            r <<= 1;
            r += (n & 1);
            n >>= 1;
        }
        
        printf ("%llu\n", r);
    }
    
    return 0;
}