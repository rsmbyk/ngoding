#include <cstdio>
#include <cstdlib>
int a, b, c, d, e, f, k, m, n;

bool isSame () {
    return (a == c && b == d) || (a == e && b == f);
}

bool isEdge () {
    if (a == 1 || b == 1) return true;
    return a == n || b == m;
}

bool isDiagonal (int p, int q) {
    return abs (a-p) == abs (b-q);
}

bool isBetween (int c1, int c2) {
    return (c1-a) * (a-c2) >= 0;
}

bool canEscape () {
    if (isSame ()) return false;
    if (isEdge ()) return true;
    if (!isDiagonal (c, d) || !isDiagonal (e, f)) return true;
    return !(isBetween (c, e) && isBetween (d, f));
}

int main (int argc, char **argv) {
    scanf ("%d %d", &n, &m);
    scanf ("%d", &k);
    
    while (k--) {
        scanf ("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
        printf ("%s\n", canEscape () ? "YES" : "NO");
    }
}