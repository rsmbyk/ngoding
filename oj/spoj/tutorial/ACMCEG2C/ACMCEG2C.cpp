#include <cstdio>
#include <deque>

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

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, k;
        scanf ("%d %d", &n, &k);
        int value[n];
        std::deque<int> candies;
        
        for (int i = 0; i < k; i++) {
            value[i] = getNumb ();
            while (!candies.empty () && value[i] >= value[candies.back ()])
                candies.pop_back ();
            
            candies.push_back (i);
        }
        printf ("%d ", value[candies.front ()]);
        
        for (int i = k; i < n; i++) {
            value[i] = getNumb ();
            while (!candies.empty () && candies.front () <= i-k) candies.pop_front ();
            while (!candies.empty () && value[i] >= value[candies.back ()]) candies.pop_back ();
            candies.push_back (i);
            printf ("%d ", value[candies.front ()]);
        }
        printf ("\n");
    }
    return 0;
}