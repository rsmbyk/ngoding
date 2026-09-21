#include <cstdio>

int main () {
    int tc;
    scanf ("%d", &tc);
    
    for (int x = 0; x < tc; x++) {
        int n, s, digits = 1, allowed;
        scanf ("%d %d", &n, &allowed);
        s = allowed;
        
        while (true) {
            if (s % n == 0) {
                printf ("Case %d: %d\n", x+1, digits);
                break;
            }
            else {
                s = s % n;
                s *= 10;
                s += allowed;
                digits++;
            }
        }
    }
    
    return 0;
}