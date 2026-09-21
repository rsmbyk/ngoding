#include <cstdio>

int main (int argc, char **argv) {
    long long tc, n;
    scanf ("%lld", &tc);
    
    while (tc--) {
        scanf ("%lld", &n);
        if (n % 3 == 0) printf ("Ragini\n");
        else printf ("Hemlata\n");
    }
    
    return 0;
}