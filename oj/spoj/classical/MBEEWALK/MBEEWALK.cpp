#include <cstdio>
#define depth 17
int dp[14+1][depth][depth];

int main (int argc, char **argv) {
    int tc, n;
    
    dp[0][8][8] = 1;
    
    for (int i = 1; i <= 14; i++) {
        for (int j = 1; j <= depth; j++) {
            for (int k = 1; k <= depth; k++) {
                dp[i][j][k]
                    = dp[i-1][j-1][k] + dp[i-1][j-1][k+1]
                    + dp[i-1][j][k+1] + dp[i-1][j+1][k]
                    + dp[i-1][j+1][k-1] + dp[i-1][j][k-1]
                ;
            }
        }
    }
    
    scanf ("%d", &tc);
    while (tc--) {
        scanf ("%d", &n);
        printf ("%d\n", dp[n][8][8]);
    }
    
    return 0;
}