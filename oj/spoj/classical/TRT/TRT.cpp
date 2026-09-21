#include <cstdio>
#include <algorithm>

int dp[2002][2002];
int v[2002];

int trt (int i, int j, int a) {
    if (i > j)
        return 0;
    if (dp[i][j] == 0)
        dp[i][j] = std::max (trt (i+1, j, a+1) + v[i]*a, trt (i, j-1, a+1) + v[j]*a);
    return dp[i][j];
}

int main (int argc, char **argv) {
    int n;
    scanf ("%d", &n);
    
    for (int i = 0; i < n; i++)
        scanf ("%d", &v[i]);
    printf ("%d\n", trt (0, n-1, 1));
    return 0;
}