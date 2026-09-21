#include <cstdio>
#include <deque>
#include <climits>

int main () {
    int Tc;
    scanf ("%d", &Tc);
    
    for (int tc = 1; tc <= Tc; tc++) {
        std::deque<int> basket;
        char op;
        int n, mangoSize;
        int *max = new int (INT_MIN);
        
        scanf ("%d", &n);
        printf ("Case %d:\n", tc);
        
        while (n--) {
            while (true) {
                scanf ("%c", &op);
                if (op == ' ' || op == '\n') continue;
                else break;
            }
            
            if (op == 'A') {
                scanf ("%d", &mangoSize);
                basket.push_back (mangoSize);
                if (mangoSize > *max) max = &basket.back ();
            }
            else if (op == 'R') {
                if (!basket.empty ()) {
                    if (max == &basket.back ()) {
                        *max = 0;
                        for (std::deque<int>::iterator it = basket.begin (); it < basket.end (); it++) {
                            if (*it > *max) max = &(*it);
                        }
                    }
                    basket.pop_back ();
                }
            }
            else {
                if (basket.empty ()) printf ("Empty\n");
                else printf ("%d\n", *max);
            }
        }
    }
}