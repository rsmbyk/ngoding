#include <cstdio>
#include <queue>
#define asc_pq std::priority_queue<int, std::vector<int>, std::greater<int> >
void mid ();
void push (int);
std::priority_queue<int> l;
asc_pq r;

int main (int argc, char const *argv[]) {
    int tc, n;
    scanf ("%d", &tc);
    
    while (tc--) {
        while (scanf ("%d", &n) && n) {
            if (n == -1) mid ();
            else push (n);
        }
        printf ("\n");
        l = std::priority_queue<int> ();
        r = asc_pq ();
    }
    return 0;
}

void mid () {
    printf ("%d\n", l.top ());
    l.pop ();
    if (l.size () < r.size ()) {
        int n = r.top ();
        r.pop ();
        push (n);
    }
}

void push (int n) {
    if (r.size () < l.size ()) {
        if (!l.empty () && n <= l.top ()) {
            int swap = n;
            n = l.top ();
            
            l.pop ();
            l.push (swap);
        }
        
        r.push (n);
    }
    else {
        if (!r.empty () && n >= r.top ()) {
            int swap = n;
            n = r.top ();
            
            r.pop ();
            r.push (swap);
        }
        
        l.push (n);
    }
}