#include <cstdio>
#define MOD 1000000007

long long mod_exp (long long n, int mod) {
    if (n <= 3) return n;
    else {
        long long a, b, res;
        a = mod_exp (n/2, mod);
        b = n % 2 == 0 ? a : mod_exp ((n/2)+1, mod);
        res = (a * b) % mod;
        return res;
    }
}

int main (int argc, char const *args[]) {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        long long n, rupees;
        scanf ("%lld", &n);
        rupees = mod_exp (n, MOD);
        printf ("%lld\n", rupees);
    }
    
    return 0;
}