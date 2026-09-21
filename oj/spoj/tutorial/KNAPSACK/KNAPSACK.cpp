#include <cstdio>

int main (int argc, char **argv) {
    int x, m;
    scanf ("%d %d", &x, &m);
    
    int w[m+1];
    float p[m+1];
    for (int i = 1; i <= m; i++)
        scanf ("%d %f", &w[i], &p[i]);
    
    float *prev = new float[m+1];
    float *now = new float[m+1];
    
    for (int i = 0; i <= x; i++)
        for (int j = 1; j <= m; j++)
            if (w[i])
}