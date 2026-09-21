#include <cstdio>
#include <algorithm>

int n, k, min[101], price[101];

void compute () {
    for (int i = 1; i <= k; i++) {
        min[i] = price[i];
        
        for (int j = 1; j < i; j++) {
            if (min[j] == -1 || min[i-j] == -1) continue;
            int temp = min[j] + min[i-j];
            if (min[i] == -1) min[i] = temp;
            else min[i] = std::min (min[i], temp);
        }
    }
}

int main (int args, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &n, &k);
        for (int i = 1; i <= k; i++) scanf ("%d", &price[i]);
        compute ();
        printf ("%d\n", min[k]);
    }
}