#include <cstdio>
#define MOD 1000000007
long long cat[2501]={0};

long long f (int);

int main() {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n;
        scanf ("%d", &n);
        
        if (n % 2 != 0) printf ("0\n");
        else printf ("%lld\n", f (n/2));
    }
    
    return 0;
}

long long f (int n) {
    if (n <= 1) return 1;
    else {
        if (cat[n] == 0) {
            for (int x = 0; x < n; x++) {
                cat[n] = (cat [n] + (f (x) * f (n-x-1)) % MOD) % MOD;
            }
        }
        return cat[n];
    }
}
