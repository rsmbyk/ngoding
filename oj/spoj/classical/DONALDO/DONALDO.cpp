#include <cstdio>
#include <queue>
#include <algorithm>

long long getNumb ();

int main (int argc, char **argv) {
    int tc, n, I, input;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d", &n);
        std::vector<long long> numbs;
        std::queue<long long> texts;
        
        for (int i = 0; i < n; i++) numbs.push_back (getNumb ());
        std::sort (numbs.begin (), numbs.end ());
        scanf ("%d", &I);
        int gf = 0;
        
        for (int i = 0; i < n; i++) {
            texts.push (numbs[i]);
            if (numbs[i]-texts.front () < I) continue;
            gf = std::max (gf, (int) (texts.size () - 1));
            long long temp = texts.front ();
            while (!texts.empty () && temp == texts.front ())
                texts.pop ();
        }
        
        printf ("Case %d: %d\n", t, std::max (gf, (int) (texts.size ())));
    }
}

long long getNumb () {
    int h, m, s;
    scanf ("%d:%d:%d", &h, &m, &s);
    
    return (long long) ((h * 3600) + (m * 60) + s);
}