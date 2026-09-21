#include <cstdio>
#include <stack>

int main (int argc, char const *argv[]) {
    int n, p, s, f, movement=0;
    scanf ("%d %d", &n, &p);
    std::stack<int> strings[7];
    
    while (n--) {
        scanf ("%d %d", &s, &f);
        if (strings[s].empty ()) strings[s].push (f), movement++;
        else {
            while (!strings[s].empty ()) {
                if (strings[s].top () > f) strings[s].pop (), movement++;
                else if (strings[s].top () < f) strings[s].push (f), movement++;
                else break;
            }
            
            if (strings[s].empty ()) strings[s].push (f), movement++;
        }
    }
    
    printf ("%d\n", movement);
}