#include <vector>
#include <cstdio>

using namespace std;

int getNumb () {
    int r=0;
    int c;
    
    while (true) {
        c = getchar_unlocked ();
        if (c == EOF) return EOF;
        if (c == ' ' || c == '\n') continue;
        else break;
    }
    
    if (c != '-') r = r + c - '0';
    
    while (true) {
        c = getchar_unlocked ();
        if (c == EOF) return EOF;
        if (c >= '0' && c <= '9') r = 10 * r + c -'0';
        else break;
    }
    
    return r;
}

int main (int argc, char **argv) {
    int n, tc=1, maxn=0;
    vector<int> cube;
    
    for (int i = 2; ; i++) {
        int c = i*i*i;
        if (c > 100000) break;
        cube.push_back (c);
    }
    
    int dp[100001];
    
    while ((n = getNumb ()) != EOF) {
        if (n > maxn) {
            for (int i = maxn; i <= n; i++) {
                dp[i] = i;
                for (int j = 0; j < cube.size (); j++)
                    if (cube[j] <= i)
                        dp[i] = min (dp[i], dp[i-cube[j]] + 1);
            }
            
            maxn = n;
        }
        
        printf ("Case #%d: %d\n", tc++, dp[n]);
    }
}