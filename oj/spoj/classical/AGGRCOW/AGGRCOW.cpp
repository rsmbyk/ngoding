#include <cstdio>
#include <algorithm>

bool valid (int *stall, int n, int c, int m) {
    int cows=1, prev=stall[0];
    for (int i = 1; i < n; i++) {
        if (stall[i] - prev >= m) {
            prev = stall[i];
            cows++;
            if (cows == c) return true;
        }
    }
    return false;
}

int main (int argc, char **argv) {
    int tc, n, c;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &n, &c);
        int x[n];
        for (int i = 0; i < n; i++) scanf ("%d", &x[i]);
        std::sort (x, x+n);
        
        int l, r, ans;
        l = 0;
        r = x[n-1];
        ans = 0;
        
        while (l <= r) {
            int m = (l+r) / 2;
            if (valid (x, n, c, m)) {
                ans = std::max (ans, m);
                l = m + 1;
            }
            else r = m - 1;
        }
        
        printf ("%d\n", ans);
    }
}