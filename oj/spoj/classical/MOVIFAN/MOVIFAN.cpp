#include <cstdio>
#include <algorithm>
#define MOD 1000000007

int main (int argc, char const *argv[]) {
    int tc, n, m;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &n, &m);
        int numb[n+1], max[n+1]={0, 1};
        for (int i = 0; i < n; i++) scanf ("%d", &numb[i]);
        std::sort (numb, numb+n);
        
        for (int i = 2; i <= n; i++) {
            int j = i - 1;
            while (j > 0 && numb[j-1] > numb[i-1]-m) j--;
            max[i] = (max[i-1] + max[j] + 1) % MOD;
        }
        
        printf ("%d\n", max[n]);
    }
    
    return 0;
}