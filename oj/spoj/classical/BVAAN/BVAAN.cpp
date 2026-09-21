#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int l[101][101];

int knapsack (char *a, char *b, int m, int n) {
    int k[101][101]={};
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (a[i-1] == b[j-1])
                k[i][j] = k[i-1][j-1] + b[j-1];
            else
                k[i][j] = max (k[i-1][j], k[i][j-1]);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++)
            printf ("%d ", k[i][j]);
        printf ("\n");
    }
    return k[m][n];
}

void lcs (string a, string b) {
    for (int i = 1; i <= a.length (); i++) {
        for (int j = 1; j <= b.length (); j++)
            if (a[i-1] == b[j-1])
                l[i][j] = l[i-1][j-1] + 1;
            else
                l[i][j] = max (l[i-1][j], l[i][j-1]);
    }
}

/*
 * not solved yet.
 * problem: cara membatasi jumlah huruf yang diambil sebanyak k saja.
 */

int main (int argc, char **argv) {
    char a[101], b[101];
    int tc, m, n, k;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%s", a);
        scanf ("%s", b);
        m = strlen (a);
        n = strlen (b);
        scanf ("%d", &k);
        
        lcs (a, b);
        printf ("%d: %d\n", tc, knapsack (a, b, m, n));
    }
}