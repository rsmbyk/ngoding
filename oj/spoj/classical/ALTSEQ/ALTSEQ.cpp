#include <algorithm>
#include <cstdio>
typedef long long int lli;

bool isSameSign (lli a, lli b) {
    return (a * b) >= 0;
}

int main (int argc, char **argv) {
    int n;
    scanf ("%d", &n);
    
    lli numb[n];
    for (int i = 0; i < n; i++) scanf ("%lld", &numb[i]);
    
    lli ans=0, seq[n]={};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (llabs (numb[i]) > llabs (numb[j]) && !isSameSign (numb[i], numb[j]))
                seq[i] = std::max (seq[i], seq[j]+1);
        
        ans = std::max (ans, seq[i]);
    }
    
    printf ("%lld\n", ans+1);
}