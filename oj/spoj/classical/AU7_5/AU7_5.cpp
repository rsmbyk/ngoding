#include <cstdio>
int const MOD = 5000011;
int dp[2][100001];

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, k;
        scanf ("%d %d", &n, &k);
        dp[0][1] = dp[1][1] = 1;
        
        for (int i = 2; i <= n; i++) {
            dp[0][i] = (dp[0][i-1] + dp[1][i-1]) % MOD;
            if (i-k-1 > 0) dp[1][i] = (dp[0][i-k-1] + dp[1][i-k-1]) % MOD;
            else dp[1][i] = 1;
        }
        
        printf ("%d\n", (dp[0][n] + dp[1][n]) % MOD);
    }
    
    return 0;
}