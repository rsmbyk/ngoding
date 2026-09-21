#include <cstdio>
#include <cstring>

int main (int argc, char **argv) {
    int tc, n;
    int dp[125521];
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        memset (dp, 0, sizeof dp);
        dp[0] = 1;
        int sum = 0;
        int student[n];
        for (int i = 0; i < n; i++) {
            scanf ("%d", &student[i]);
            sum += student[i];
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = sum/2; j >= student[i]; j--) {
                if (dp[j - student[i]]) dp[j] = 1;
            }
        }
        
        int max = sum/2;
        while (!dp[max] && max>=0) max--;
        printf ("%d\n", sum - (2*max));
    }
}