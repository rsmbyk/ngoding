#include <cstdio>
#include <algorithm>
#define DEPTH 50000
using namespace std;
int depth = DEPTH;
int dp[DEPTH];

int f (int i) {
    if (i <= depth) return dp[i];
    if (i%2 == 0 && i%3 != 0) return 1 + min (f (i/2), f (i-1));
    else if (i%3 == 0 && i%2 != 0) return 1 + f (i/3);
    else if (i%2 == 0 && i%3 == 0) return 1 + min (f (i/3), min (f (i/2), f (i-1)));
    else return 1 + f (i-1);
}

int main (int argc, char **argv) {
    int tc, n;
    scanf ("%d", &tc);
    
    dp[1]=0, dp[2]=1;
    for (int i = 3; i <= depth; i++) {
        if (i%2 == 0 && i%3 != 0) dp[i] = min (dp[i/2], dp[i-1]);
        else if (i%3 == 0 && i%2 != 0) dp[i] = dp[i/3];
        else if (i%2 == 0 && i%3 == 0) dp[i] = min (dp[i-1], min (dp[i/2], dp[i/3]));
        else dp[i] = dp[i-1];
        dp[i]++;
    }
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d", &n);
        printf ("Case %d: %d\n", t, f (n)); }
    return 0;
}