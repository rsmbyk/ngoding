#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define MAX_N 10000000

std::vector<int> prime;
int div[MAX_N+1] = {};

void generate_prime () {
    for (int x = 2; x <= MAX_N; x++) {
        if (div[x] == 0) {
            prime.push_back (x);
            for (int i = x; i <= MAX_N; i+=x) div[i] = x;
        }
    }
}

int main (int args, char const *argv[]) {
    int tc;
    generate_prime ();
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        long long n, depth=0;
        scanf ("%lld", &n);
        
        if (n % 2 == 0) depth = (n/2) - 1;
        else if (n <= MAX_N && div[n] != n) depth = (n - div[n]) / 2;
        else {
            for (int i = 0; i < prime.size (); i++) {
                if (n % prime[i] == 0) {
                    if (i < prime.size ()) depth = (n - prime[i]) / 2;
                    break;
                }
            }
        }
        
        printf ("Case #%d: %lld\n", t, depth);
    }
    
    return 0;
}