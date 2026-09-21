#include <cstdio>
#include <cstring>
#define MOD 1000000007

int cal (long long M, long long N) {
    long long comb = (N * (N-1)) / 2;
    if (M-comb < 0) return 0;
    int p[M-comb+1][N+1];
    
    for (int n = 0; n <= M-comb; n++) {
        for (int k = 0; k <= N; k++) {
            if (k > n) p[n][k] = 0;
            else if (k == n) p[n][k] = 1;
            else if (k == 0) p[n][k] = 0;
            else p[n][k] = (p[n-1][k-1] + p[n-k][k]) % MOD;
            if (p[n][k] < 0) p[n][k] += MOD;
        }
    }
    
    return p[M-comb][N];
}

int main () {
    int tc, n, m;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d %d", &m, &n);
        printf ("Case %d: %d\n", t, cal (m, n));
    }
    
    return 0;
}