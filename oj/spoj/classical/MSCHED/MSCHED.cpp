#include <queue>
#include <cstdio>
#define poii pair<int, int>
using namespace std;

pair<int, int> getPair () {
    int a, b;
    scanf ("%d %d", &a, &b);
    return make_pair (b, a);
}

int main (int argc, char **argv) {
    int n;
    scanf ("%d", &n);
    priority_queue<poii, vector<poii >, greater<poii > > cows;
    for (int i = 0; i < n; i++) cows.push (getPair ());
    
    priority_queue<int, vector<int>, greater<int> > s;
    int t = 1;
    while (!cows.empty ()) {
        while (cows.top ().first == t) {
            s.push (cows.top ().second);
            if (s.size () > t) s.pop ();
            cows.pop ();
            if (cows.empty ()) break;
        }
        t++;
    }
    
    int total = 0;
    while (!s.empty ()) total += s.top (), s.pop ();
    printf ("%d\n", total);
}