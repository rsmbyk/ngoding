#include <algorithm>
#include <cstdio>
#include <cmath>

int f (int n) {
    for (int i = (int) ceil (sqrt (n)); i < n; i++)
        if (n % i == 0) return i;
    return n;
}

int main (int argc, char const *argv[]) {
    int a, b;
    scanf ("%d %d", &a, &b);
    a = f (a);
    b = f (b);
    printf ("%d\n", std::max (0, b-a));
    return 0;
}