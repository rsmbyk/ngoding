#include <cstdio>

long double C (int, int);

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, a, b, c, r = 3;
        scanf ("%d %d %d %d", &n, &a, &b, &c);
        
        long double eq1, eq2, eq3;
        eq1 = C (n+r, r) - C (n-a+2, r) - C (n-b+2, r) - C (n-c+2, r);
        eq2 = C (n-a-b+1, r) + C (n-a-c+1, r) + C (n-b-c+1, r);
        eq3 = C (n-a-b-c, r);
        printf ("%.0Lf\n", eq1 + eq2 - eq3);
    }
    
    return 0;
}

long double C (int n, int r) {
    if (n < r) return 0;
    
    long double res = 1;
    for (int x = n-r+1; x <= n; x++) res *= x;
    for (int x = 2; x <= r; x++) res /= x;
    return res;
}
