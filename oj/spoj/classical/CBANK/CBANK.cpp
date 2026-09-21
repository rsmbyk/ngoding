#include <cstdio>
#define MOD 1000000007

long long mod_exp (long long b, long long e, long long m) {
    long long r = 1;
    while (e > 0) {
        if ((e&1) == 1) r = (r*b) % m;
        e >>= 1;
        b = (b*b) % m;
    }
    return r;
}

int main (int argc, char **argv) {
    long long tc, n;
    scanf ("%lld", &tc);
    
    while (tc--) {
        scanf ("%lld", &n);
        
        long long n1n2, inv6;
        n1n2 = ((n-1) * (n-2)) % MOD;
        inv6 = mod_exp (6, MOD-2, MOD) % MOD;
        
        long long ans, ans1, ans2, ans3, ans4;
        ans1 = 4;
        ans2 = (6 * (n-1)) % MOD;
        ans3 = (2 * n1n2) % MOD;
        ans4 = (((n1n2 * (n-3)) % MOD) * inv6) % MOD;
        ans = (((((ans1 + ans2) % MOD) + ans3) % MOD) + ans4) % MOD;
        printf ("%lld\n", ans);
    }
    
    return 0;
}