#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> poii;

bool comparator (poii a, poii b) {
    return a.first + a.second > b.first + b.second;
}

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

poii get () {
    int m, s;
    m = getNumb ();
    s = getNumb ();
    return make_pair (m, s);
};


int main (int argc, char **argv) {
    int tc, n;
    tc = getNumb ();
    
    while (tc--) {
        n = getNumb ();
        
        vector<poii > laptops;
        vector<poii > skyline;
        for (int i = 0; i < n; i++) laptops.push_back (get ());
        sort (laptops.begin (), laptops.end (), comparator);
        
        for (int i = 0; i < n; i++) {
            bool dominant = true;
            
            for (int j = 0; j < skyline.size (); j++) {
                if (laptops[i].first == skyline[j].first && laptops[i].second == skyline[j].second)
                    continue;
                if (laptops[i].first <= skyline[j].first && laptops[i].second <= skyline[j].second) {
                    dominant = false;
                    break;
                }
            }
            
            if (dominant)
                skyline.push_back (laptops[i]);
        }
        
        sort (skyline.begin (), skyline.end (), greater<poii > ());
        
        printf ("%lu\n", skyline.size ());
        for (int i = 0; i < skyline.size (); i++)
            printf ("%d %d\n", skyline[i].first, skyline[i].second);
    }
    
    return 0;
}