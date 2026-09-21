#include <cstdio>
#include <algorithm>
int teresa[1001], blueberries[1001], k;

int grab (int i) {
    if (i < 0) return 0;
    if (teresa[i] == 0) {
        teresa[i] = std::max (teresa[i-2], teresa[i-3]);
        if (teresa[i] + blueberries[i] <= k) teresa[i] += blueberries[i];
    }
    return teresa[i];
}

int main (int argc, char const *argv[]) {
    int tc, n;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d %d", &n, &k);
        for (int i = 0; i < n; i++) scanf ("%d", &blueberries[i]);
        for (int i = 0; i < n; i++) teresa[i] = 0;
        printf ("Scenario #%d: %d\n", t, std::max (grab (n-1), grab (n-2)));
    }
}