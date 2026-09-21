#include <cstdio>
#include <cmath>

int main () {
    int r, n;
    scanf ("%d %d", &r, &n);
    printf ("%.1lf\n", 2.0 * n * r * sin (3.14/n));
    return 0;
}