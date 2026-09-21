#include <cstdio>
#define maxn 10000001
unsigned long long aps[10000001]={};

void sieve () {
    for (unsigned int i = 2; i <= maxn; i++) {
        if (!aps[i]) {
            for (int j = 1; i*j <= maxn; j++) {
                if (aps[i*j]) continue;
                aps[i*j] = i;
            }
        }
        
        aps[i] += aps[i-1];
    }
}

int main (int argc, char const *argv[]) {
    int tc, n;
    scanf ("%d", &tc);
    sieve ();
    
    while (tc--) {
        scanf ("%d", &n);
        printf ("%lld\n", aps[n]);
    }
    return 0;
}