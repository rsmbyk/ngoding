#include <cstdio>
#include <cstring>
int save[1001][1001];

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

int josephus (int n, int k) {
    if (n == 1) return 1;
    if (save[n][k] == -1)
        save[n][k] = (josephus (n-1, k) + k-1) % n + 1;
    return save[n][k];
}

int main (int argc, char **argv) {
    int tc, n, m, o;
    scanf ("%d", &tc);
    memset (save, -1, sizeof save);
    // for (int i = 0; i <= 1000; i++) for (int j = 0; j <= 1000; j++) save[i][j] = -1;
    
    while (tc--) {
        n = getNumb ();
        m = getNumb ();
        o = getNumb ();
        printf("%d\n", ((m + josephus (n, o) - 1) % n) + 1);
    }
    return 0;
}