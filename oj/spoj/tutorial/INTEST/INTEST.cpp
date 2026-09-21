#include <cstdio>

int getNumb () {
    int r=0;
    int c;
    
    while (true) {
        c = getchar_unlocked ();
        if (c == ' ' || c == '\n') continue;
        else break;
    }
    
    if (c != '-') r = r + c - '0';
    
    while (true) {
        c = getchar_unlocked ();
        if (c >= '0' && c <= '9') r = 10 * r + c -'0';
        else break;
    }
    
    return r;
}

int main () {
    int x, n, k, count=0;
    n = getNumb ();
    k = getNumb ();
    
    while (n--) {
        x = getNumb ();
        if (x % k == 0) count++;
    }
    
    printf ("%d\n", count);
}