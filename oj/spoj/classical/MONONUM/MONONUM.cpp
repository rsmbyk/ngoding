#include <cstdio>

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n;
        scanf ("%d", &n);
        
        double x = (n + 9.0) / 9.0;
        double y = 1.0;
        
        for (int i = 1; i < 9; i++) {
            y *= (i + n);
        }
        
        printf ("%.6lf\n", x - (40320.0 / y));
    }
    
    return 0;
}