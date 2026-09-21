#include <cstdio>

int main () {
    long long orders[2001] = {1, 1};
    int n, m;
    scanf ("%d %d", &n, &m);
    
    if (n > 3) {
        for (int x = 4; x <= n; x++) {
            long long t1, t2, t3, t4;
            t1 = (((x+1) % m) * (orders[x-1] % m)) % m;
            t2 = (((x-2) % m) * (orders[x-2] % m)) % m;
            t3 = (((x-5) % m) * (orders[x-3] % m)) % m;
            t4 = (((x-3) % m) * (orders[x-4] % m)) % m;
            orders[x] = (t1 - t2 - t3 + t4) % m;
        }
    }
    
    long long result = orders[n];
    while (result < 0) result += m;
    printf ("%lld\n", result);
    return 0;
}