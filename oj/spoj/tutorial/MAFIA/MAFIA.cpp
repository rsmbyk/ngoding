#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

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

int main (int args, char const *argv[]) {
    int n, s, f;

    scanf ("%d", &n);
    vector<pair<int, int> > sch;
    
    for (int i = 0; i < n; i++) {
        s = getNumb ();
        f = getNumb ();
        sch.push_back (make_pair (f, s));
    }
    
    sort (sch.begin (), sch.end ());
    
    int ch = 1;
    int end = sch[0].first;
    for (int i = 0; i < n; i++) {
        if (sch[i].second > end ) {
            end = sch[i].first;
            ch++;
        }
    }
    
    printf ("%d\n", ch);
    return 0;
}