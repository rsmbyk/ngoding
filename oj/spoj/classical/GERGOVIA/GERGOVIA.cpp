#include <cstdio>
#include <cstdlib>

int main (int argc, char **argv) {
    long long n, a, wine, work;
    
    while (scanf ("%lld", &n) && n > 0) {
        work = wine = 0;
        
        for (int i = 0; i < n; i++) {
            scanf ("%lld", &a);
            work += llabs (wine);
            wine += a;
        }
        
        printf ("%lld\n", work);
    }
    
    return 0;
}