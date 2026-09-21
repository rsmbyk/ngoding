#include <stdio.h>

int main () {
    int n, m, maxHeight, *trees;
    scanf("%d %d", &n, &m);
    trees = new int[n];
    maxHeight = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &trees[i]);
        if (trees[i] > maxHeight) maxHeight = trees[i];
    }
    
    int imin, imax;
    imin = 0;
    imax = maxHeight - 1;
    
    while (imax >= imin) {
        long long temp = 0, tmp = 0;
        int imid = (imax + imin) / 2;
        
        for (int x = 0; x < n; x++) {
            if (trees[x] > imid) temp += (trees[x] - imid);
            if (trees[x] > imid+1) tmp += (trees[x] - (imid+1));
        }
        
        if (temp >= m) {
            if (tmp < m) {
                maxHeight = imid; break;
            }
            else imin = imid + 1;
        }
        else imax = imid - 1;
    }
    
    printf ("%d\n", maxHeight);
}