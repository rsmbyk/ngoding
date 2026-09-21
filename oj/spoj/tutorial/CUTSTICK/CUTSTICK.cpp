#include <cstdio>

int main () {
    int fib[41] = {0, 1}, n;
    
    for (int x = 2; x < 41; x++) {
        fib[x] = fib[x-1] + fib[x-2];
    }
    
    while (scanf ("%d", &n) != EOF) {
        int sticks = 0;
        
        for (int x = 1; x < 41; x++) {
            if (n >= fib[x]) {
                n -= fib[x];
                sticks++;
            }
            else {
                printf ("%d\n", sticks);
                break;
            }
        }
    }
    
    return 0;
}