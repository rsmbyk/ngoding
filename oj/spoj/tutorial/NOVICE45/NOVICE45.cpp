#include <cstdio>
#define MOD 1000000007
int part[10001][101]={0};

int P (int, int);

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, k;
        scanf ("%d %d", &n, &k);
        
        int res=0;
        for (int x = 1; x <= k; x++) {
            res = (res + P (n, x)) % MOD;
        }
        
        printf ("%d\n", res);
    }
    
    return 0;
}

int P (int n, int k) {
    if (n == k) return 1;
    if (k > n || k == 0) return 0;
    else {
        if (part[n][k] == 0) {
            part[n][k] = (P (n-1, k-1) + P (n-k, k)) % MOD;
        }
        return part[n][k];
    }
}
