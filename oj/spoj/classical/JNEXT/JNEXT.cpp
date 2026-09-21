#include <cstdio>
#include <iostream>

int main (int argc, char const *argv[]) {
    int tc, n;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        int numb[n];
        for (int i = 0; i < n; i++) scanf ("%d", &numb[i]);
        
        int p = n-2;
        while (p >= 0 && numb[p] >= numb[p+1]) p--;
        
        if (p < 0) printf ("-1\n");
        else {
            int s = n-1;
            while (numb[s] <= numb[p]) s--;
            
            std::swap (numb[p], numb[s]);
            for (int i = 0; i <= p; i++) printf ("%d", numb[i]);
            for (int i = n-1; i > p; i--) printf ("%d", numb[i]);
            printf ("\n");
        }
    }
    
    return 0;
}