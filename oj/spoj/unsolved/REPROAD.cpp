#include <cstdio>
#include <queue>

int main (int argc, char **argv) {
    int tc, n, k, c;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &n, &k);
        bool r[n];
        
        for (int i = 0; i < n; i++)
            scanf ("%d", &r[i]);
        
        int i, j, res;
        i = j = res = 0;
        
        for (int l = 0; l < k && j < n; j++) {
            if (!r[j]) {
                l++;
                if (l == k)
                    break;
            }
        }
        
        while (j < n) {
            printf ("%d %d\n", i, j);
            res = std::max (res, j-i+1);
            while (r[++i]);
            while (r[++j]);
        }
        
        res = std::max (res, j-i+1);
        printf ("%d\n", res);
    }
}