#include <algorithm>
#include <cstdio>
using namespace std;

int main (int argc, char **argv) {
    int tc, n;
    scanf ("%d\n", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
    
        int numb[n];
        for (int i = 0; i < n; i++) scanf ("%d", &numb[i]);
    
        int ans=0, lis[n]={}, lds[n]={};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                if (numb[i] > numb[j]) lis[i] = max (lis[i], lis[j]+1);
        
        for (int i = n-1; i >= 0; i--) {
            for (int j = n-1; j > i; j--)
                if (numb[i] > numb[j]) lds[i] = max (lds[i], lds[j]+1);
            ans = max (ans, lis[i]+lds[i]);
        }

        printf ("%d\n", ans + 1);
    }
}