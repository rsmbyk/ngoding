#include <cstdio>
#include <climits>
#include <algorithm>

int const range[] = {100, 900, 9000, 990000, INT_MAX};
int const price[] = {2, 3, 5, 7, 11};

int toLiter (int bill) {
    int liter = 0;
    for (int i = 0; i < 5 && bill > 0; i++) {
        int temp = std::min (bill, range[i] * price[i]);
        bill -= temp;
        liter += (temp / price[i]);
    }
    return liter;
}

int toBill (int liter) {
    int bill = 0;
    for (int i = 0; i < 5 && liter > 0; i++) {
        int temp = std::min (liter, range[i]);
        liter -= temp;
        bill += (temp * price[i]);
    }
    return bill;
}

int find (int sum, int diff) {
    int l, r;
    l = 0;
    r = sum;
    
    while (l <= r) {
        int m, a, b;
        m = (l + r) / 2;
        a = toBill (m);
        b = toBill (sum-m);
        
        if (b-a == diff) return a;
        if (b-a > diff) l = m + 1;
        else r = m - 1;
    }
    
    return -1;
}

int main (int argc, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        int bill, diff, res;
        scanf ("%d %d", &bill, &diff);
        res = find (toLiter (bill), diff);
        printf ("Case #%d: %d %d\n", t, res, res+diff);
    }
    
    return 0;
}

