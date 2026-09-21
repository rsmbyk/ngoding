#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

int main (int argc, char **argv) {
    string a, b;
    while (cin >> a >> b) {
        int m, n;
        m = a.length ();
        n = b.length ();
        int lcs[m+1][n+1]={};
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (a[i-1] == b[j-1])
                    lcs[i][j] = lcs[i-1][j-1] + 1;
                else
                    lcs[i][j] = max (lcs[i-1][j], lcs[i][j-1]);
        
        stack<char> res;
        int i, j;
        for (i=m, j=n; i > 0 && j > 0; ) {
            if (a[i-1] == b[j-1]) {
                res.push (a[i-1]);
                i--; j--; }
            else if (lcs[i-1][j] > lcs[i][j-1])
                res.push (a[--i]);
            else
                res.push (b[--j]);
        }
        
        while (j--) res.push (b[j]);
        while (i--) res.push (a[i]);
        while (!res.empty ())
            printf ("%c", res.top ()), res.pop ();
        printf ("\n");
    }
}