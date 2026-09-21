#include <cstdio>

int main (int argc, char **argv) {
    int tc, n, q, m, r;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d %d", &n, &q, &m);
        
        int v[n];
        for (int i = 0; i < n; i++)
            scanf ("%d", &v[i]);
    
        bool *prev = new bool[m+1] ();
        bool *now = new bool[m+1] ();
        now[q] = true;
        
        for (int i = 0; i < n; i++) {
            bool *tmp = now;
            now = prev;
            prev = tmp;
            
            for (int j = 0; j <= m; j++) {
                if (prev[j]) {
                    if (j+v[i] <= m) now[j+v[i]] = true;
                    if (j-v[i] >= 0) now[j-v[i]] = true; }
                prev[j] = false;
            }
        }
        
        for (r = m; r >= 0; r--)
            if (now[r]) break;
        printf ("%d\n", r);
        delete prev, now;
    }
}