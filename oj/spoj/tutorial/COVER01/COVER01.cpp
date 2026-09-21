#include <cstdio>
#define MOD 100000007

long long fibonacci (int);
void multiply (long long[2][2], long long[2][2]);
void power (long long[2][2], int);

int main() {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n;
        scanf ("%d", &n);
        printf("%lld\n", fibonacci (n+1));
    }
    
    return 0;
}

long long fibonacci (int n) {
    long long F[2][2] = {{1,1}, {1,0}};
    power (F, n-1);
    return F[0][0];
}

void power (long long F[2][2], int n) {
    if (n == 0 || n == 1) return;
    
    power (F, n/2);
    multiply (F, F);
    
    if (n % 2 != 0) {
        long long M[2][2] = {{1,1}, {1,0}};
        multiply (F, M);
    }
}

void multiply (long long F[2][2], long long M[2][2]) {
    long long w, x, y, z;
    x = (((F[0][0] * M[0][0]) % MOD) + ((F[0][1] * M[1][0]) % MOD)) % MOD;
    y = (((F[0][0] * M[0][1]) % MOD) + ((F[0][1] * M[1][1]) % MOD)) % MOD;
    z = (((F[1][0] * M[0][0]) % MOD) + ((F[1][1] * M[1][0]) % MOD)) % MOD;
    w = (((F[1][0] * M[0][1]) % MOD) + ((F[1][1] * M[1][1]) % MOD)) % MOD;
    
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
