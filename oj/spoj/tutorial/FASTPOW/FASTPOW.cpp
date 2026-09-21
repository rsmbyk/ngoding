#include <cstdio>

long long logexp_mod (int a, int b, int c) {
    if (b == 1) return a;
    long long r;
    r = logexp_mod (a, b/2, c);
    r = (r * r) % c;
    if (b % 2 != 0) r = (r * a) % c;
    return r;
}

int main (int argc, char const *argv[]) {
    int a, b, c;
    scanf ("%d %d %d", &a, &b, &c);
    printf ("%lld", logexp_mod (a, b, c));
}