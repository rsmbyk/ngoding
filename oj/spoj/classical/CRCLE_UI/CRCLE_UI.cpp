#include <cstdio>
#include <cstring>

#define MOD 1000000007
#define TOTIENT 1000000006

long long power (long long k, long long n) {
    if (n == 0) return 1;
    else if (n == 1) return k % MOD;
    else {
        long long p = power (k, n/2);
        if (n % 2 == 0) return (p * p) % MOD;
        else return (((p * p) % MOD) * k) % MOD;
    }
}

long long convertToInt (char *n, int mod) {
    long long number = 0;
    int ln = strlen (n);
    
    for (int x = 0; x < ln; x++) {
        number %= mod;
        number *= 10;
        number += (n[x] - '0');
    }
    
    return number % mod;
}

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        char s_n[1111], s_k[1111];
        scanf ("%s %s", s_n, s_k);

        long long n, k, r, x;
        n = convertToInt (s_n, TOTIENT);
        k = convertToInt (s_k, MOD);
        r = power (k-1, n);
        x = power (-1, n);
        r = (r + (x * (k-1))) % MOD;
        
        if (r < 0) r = MOD + r;
        printf ("%lld\n", r);
    }
}