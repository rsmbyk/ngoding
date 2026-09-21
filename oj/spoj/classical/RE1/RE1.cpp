#include <cstdio>
#define MOD 1000000007
int dp[101][5005];

int main (int argc, char **argv) {
    for (int i = 1; i <= 100; i++) {
        int k = i*(i-1) >> 1;
        dp[i][0] = 1;
        
        for (int j = 1; j <= k; j++)
            if (j < i)
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
            else
                dp[i][j] = (((dp[i-1][j] + dp[i][j-1] - dp[i-1][j-i]) % MOD) + MOD) % MOD;
    }
    
    int tc, n, k;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d %d", &n, &k);
        if (k > 4950) printf ("0\n");
        else printf ("Case %d: %d\n", t, dp[n][k]);
    }
}