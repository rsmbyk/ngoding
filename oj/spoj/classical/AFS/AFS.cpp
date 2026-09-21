#include <cstdio>

int main (int argc, char const *argv[]) {
    long long tc, n, a, b;
    scanf ("%lld", &tc);
    
    while (tc--) {
        scanf ("%lld", &n);
        long long sum = 0;
        
        for (int i = 2; i*i <= n; i++) {
            a = i + 1;
            b = n / i;
    
            sum = sum + i;
            if (a > b) continue;
            sum = sum + ((b * (b+1)) / 2) - ((a * (a-1)) / 2);
            sum = sum + (i * (b-a+1));
        }
        
        sum = sum + (n-1);
        printf ("%lld\n", sum);
    }
    
    return 0;
}