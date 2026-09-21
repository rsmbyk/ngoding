#include <cstdio>
#include <deque>
#include <map>

int main (int argc, char const *argv[]) {
    int tc, n, q, y;
    char x;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        printf ("Case %d:\n", t);
        scanf ("%d", &n);
        
        std::deque<int> bus;
        std::map<int, int> index;
        int front=0, back=0;
        
        while (n--) {
            scanf ("%d", &q);
            x = ' ';
            while (x == ' ') scanf ("%c", &x);
            
            switch (q) {
                case 1: {
                    scanf ("%d", &y);
                    std::pair<int, int> p;
                    if (x == 'F') bus.push_front (y), front--, p = std::make_pair (y, front);
                    else bus.push_back (y), p = std::make_pair (y, back), back++;
                    index.insert (p);
                    break;
                }
                case 2: {
                    if (x == 'F') bus.pop_front (), front++;
                    else bus.pop_back (), back--;
                    break;
                }
                case 3: {
                    scanf ("%d", &y);
                    int i = index[y] - front + 1;
                    if (x == 'D') printf ("%d\n", bus[y-1]);
                    else printf ("%d\n", i);
                    break;
                }
                default: break;
            }
        }
    }
}