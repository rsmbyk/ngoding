#include <cstdio>
#include <algorithm>

int main (int argc, char const *args[]) {
    int tc, n;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d", &n);
        int coins[n], c=0, total=0;
        
        for (int i = 0; i < n; i++) scanf ("%d", &coins[i]);
        std::sort (coins, coins+n);
        for (int i = 1; i < n; i++) {
            if (total + coins[i-1] < coins[i]) {
                total += coins[i-1];
                c++;
            }
        }
        
        printf ("Case #%d: %d\n", t, n == 0 ? 0 : c+1);
    }
}