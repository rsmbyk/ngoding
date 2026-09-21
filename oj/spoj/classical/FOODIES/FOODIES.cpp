#include <cstdio>
#include <vector>
#include <queue>

int getNumb () {
    int r=0;
    int c;

    while (true) {
        c = getchar_unlocked ();
        if (c == ' ' || c == '\n') continue;
        else break;
    }

    if (c != '-') r = r + c - '0';

    while (true) {
        c = getchar_unlocked ();
        if (c >= '0' && c <= '9') r = 10 * r + c -'0';
        else break;
    }

    return r;
}

int scan () {
    return getNumb ();
}

int main () {
    int tc, n, m;
    scanf ("%d", &tc);
    
    while (tc--) {
        n = scan ();
        
        std::priority_queue<int> p;
        for (int i = 0; i < n; i++)
            p.push (scan ());
        m = scan ();
        
        unsigned long long sum = 0;
        while (m) {
            int max = p.top ();
            p.pop ();
            
            while (max >= p.top () && m) {
                sum += max;
                max--;
                m--;
            }
            
            p.push (max);
        }
        
        printf ("%llu\n", sum);
    }
}