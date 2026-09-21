#include <cstdio>
#include <stack>

int main (int argc, char **argv) {
    int tc, n;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        std::stack<int> s;
        
        if (n == 0) printf ("10");
        else if (n < 10) printf ("%d", n);
        else {
            for (int i = 9; i >= 2; i--) {
                while (n % i == 0) {
                    s.push (i);
                    n /= i;
                }
            }
    
            if (n > 10) printf ("-1");
            else {
                while (!s.empty ()) {
                    printf ("%d", s.top ());
                    s.pop ();
                }
            }
        }
        
        printf ("\n");
    }
}