#include <cstdio>

int main (int argc, char **argv) {
    int n, k;
    while (scanf ("%d %d", &n, &k)) {
        if (n == 0 && k == 0) break;
        int numb[n];
        long long table[n][k+1]={};
        
        for (int i = 0; i < n; i++) scanf ("%d", &numb[i]);
        for (int i = 0; i < n; i++) table[i][1] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 2; j <= k; j++)
                for (int a = 0; a < i; a++)
                    if (numb[i] > numb[a])
                        table[i][j] += table[a][j-1];
        
        long long total = 0;
        for (int i = 0; i < n; i++) total += table[i][k];
        printf ("%lld\n", total);
    }
    
    return 0;
}