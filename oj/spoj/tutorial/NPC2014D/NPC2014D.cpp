#include <cstdio>

int main (int argc, char const *args[]) {
    int tc, n, p;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        int max=0, maxindex;
        for (int i = 0; i < n; i++) {
            scanf ("%d", &p);
            if (p >= max) {
                max = p;
                maxindex = i;
            }
        }
        
        printf ("%d\n", max + maxindex);
    }
}