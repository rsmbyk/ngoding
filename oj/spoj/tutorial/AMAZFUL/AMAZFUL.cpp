#include <cstdio>
#define MOD 1000000007

long long mod_exp (long long b, long long e, long long m) {
    long long r = 1;
    while (e > 0) {
        if ((e & 1) == 1) r = (r * b) % m;
        e >>= 1;
        b = (b * b) % m;
    }
    return r;
}

int main (int argc, char const *args[]) {
    long long inv6 = mod_exp (6, MOD-2, MOD);
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        long long n, result;
        scanf ("%lld", &n);
        if (n & 1) result = ((mod_exp (3, n, MOD) + 3) * inv6) % MOD;
        else result = ((mod_exp (3, n, MOD) - 3) * inv6) % MOD;
        
        if (result < 0) result += MOD;
        printf ("%lld\n", result);
    }
    
    return 0;
}