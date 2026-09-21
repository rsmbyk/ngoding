#include <cstdio>
#include <cstdlib>

int main (int argc, char **argv) {
    long long tc, n, coke;
    scanf ("%lld", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%lld", &n);
        long long min=1, sum=0;
        
        while (n--) {
            scanf ("%lld", &coke);
            sum += coke;
            
            if (sum <= 0) {
                min += std::abs (sum);
                sum = 0;
            }
        }
        
        printf ("Scenario #%d: %lld\n", t, min);
    }
    
    return 0;
}