#include <algorithm>
#include <cstdio>
using namespace std;

int main (int argc, char **argv) {
    int tc, n;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        long long int toys[n+10]={}, picks[n+10];
        for (int i = 0; i < n; i++) scanf ("%lld", &toys[i]);
        
        for (int i = n-1; i >= 0; i--) {
            picks[i] = toys[i] + picks[i+2];
            picks[i] = max (picks[i], picks[i+4] + toys[i] + toys[i+1]);
            picks[i] = max (picks[i], picks[i+6] + toys[i] + toys[i+1] + toys[i+2]);
        }
        
        printf ("%lld\n", picks[0]);
    }
}