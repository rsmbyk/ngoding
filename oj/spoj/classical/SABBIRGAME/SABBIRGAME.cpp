#include <cstdio>
#include <cstdlib>

int main (int argc, char **argv) {
    long long tc, n, lifepoint;
    scanf ("%lld", &tc);
    
    while (tc--) {
        scanf ("%lld", &n);
        long long min=1, sum=0, perfect=1;
        
        while (n--) {
            scanf ("%lld", &lifepoint);
            sum += lifepoint;
            
            if (sum <= 0) {
                perfect = 0;
                min += std::abs (sum);
                sum = 0;
            }
        }
        
        if (perfect) min = 0;
        printf ("%lld\n", min);
    }
    
    return 0;
}