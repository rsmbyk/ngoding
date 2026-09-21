#include <cstdio>
#include <deque>

class Mine {
public:
    int x, g, d;
};

int main (int argc, char **argv) {
    int n;
    scanf ("%d", &n);
    
    int e=0, l=0;
    Mine m[n];
    
    for (int i = 0; i < n; i++) {
        scanf ("%d %d %d", &m[i].x, &m[i].g, &m[i].d);
        e += m[i].d;
        if (m[i].x - m[l].x <= e) {
            
        }
    }
}