#include <algorithm>
#include <cstdio>

int main (int argc, char **argv) {
    int tc, e, l;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &e, &l);
        int b[l+1], s[l+1], dp[e+1]={};
        
        for (int i = 1; i <= l; i++)
            scanf ("%d", &b[i]);
        for (int i = 1; i <= l; i++)
            scanf ("%d", &s[i]);
        
        for (int i = 0; i <= e; i++)
            for (int j = 1; j <= l; j++)
                if (b[j] <= i)
                    dp[i] = std::max (dp[i], dp[i-b[j]] + s[j]);
        
        printf ("%d\n", dp[e]);
        
    }
}