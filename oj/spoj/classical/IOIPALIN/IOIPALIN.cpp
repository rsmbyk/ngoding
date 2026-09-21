#include <algorithm>
#include <cstdio>
using namespace std;

int main (int argc, char **argv) {
    char s[5005];
    int n;
    
    scanf ("%d %s", &n, s);
    int *now = new int[n+2] ();
    int *prev = new int[n+2] ();
    
    for (int i = 1; i <= n; i++) {
        swap (now, prev);
        for (int j = n; j > 0; j--)
            if (s[i-1] == s[j-1])
                now[j] = prev[j+1] + 1;
            else
                now[j] = max (prev[j], now[j+1]);
    }
    
    printf ("%d", n-now[1]);
}