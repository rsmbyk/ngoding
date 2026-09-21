#include <cstdio>
#include <cmath>

int main (int argc, char **argv) {
    int a, b, n, s;
    scanf ("%d %d %d", &a, &b, &n);
    
    int root = (int) sqrt (b);
    int ln = b-a+1;
    int sieve[ln]={};
    
    s = (((a/2)+1) * 2) - a;
    for (int i = 0; s+i < ln; i+=2) {
        sieve[s+i]++;
        if ((s+i+a)*(s+i+a) == 
        printf ("-----%d %d\n", s+i, sieve[s+i]);
    }
    for (int i = 3; i <= b; i+=2) {
        s = (((a/i) + 1) * i) - a;
        for (int j = 0; s+j < ln; j+=i) {
            sieve[s+j]++;
            printf (">>>>>%d %d\n", s+j, sieve[s+j]);
        }
    }
    
    int ndiv = 0;
    for (int i = 0; i < b-a; i++) if (sieve[i] == n-2) printf ("'''%d\n", i), ndiv++;
    printf ("%d\n", ndiv);
}