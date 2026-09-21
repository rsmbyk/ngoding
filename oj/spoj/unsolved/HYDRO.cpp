#include <cstdio>

int main (int argc, char **argv) {
    int tc, n, h;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        int dam[n];
    
        for (int i = 0; i < n; i++)
            scanf ("%d", &dam[i]);
        
        int l, r, ml, mr, water;
        l = water = 0;
        r = n-1;
        ml = dam[l];
        mr = dam[r];
        
        while (l < r) {
            if (ml < mr) {
                if (dam[l+1] >= ml)
                    ml = dam[l+1];
                else
                    water +=
            }
        }
        
        printf ("%d\n", water);
    }
}