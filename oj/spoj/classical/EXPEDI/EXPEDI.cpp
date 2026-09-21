#include <cstdio>
#include <queue>
using namespace std;

int main (int argc, char **argv) {
    int tc, n, d, f, l, p;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
    
        priority_queue< pair<int, int> > stopsList;
        priority_queue<int> stopsCandidate;
        
        for (int i = 0; i < n; i++) {
            scanf ("%d %d", &d, &f);
            stopsList.push (make_pair (d, f));
        }
        
        stopsList.push (make_pair (0, 0));
        scanf ("%d %d", &l, &p);
        int fuelstop = 0;
        
        while (!stopsList.empty ()) {
            while (stopsList.top ().first < l-p && !stopsCandidate.empty ()) {
                p += stopsCandidate.top ();
                stopsCandidate.pop ();
                fuelstop++;
            }
    
            if (stopsList.top ().first < l-p && stopsCandidate.empty ()) {
                fuelstop = -1;
                break;
            }
            
            stopsCandidate.push (stopsList.top ().second);
            stopsList.pop ();
        }
        
        printf ("%d\n", fuelstop);
    }
    
    return 0;
}