#include <cstdio>
#include <queue>
using namespace std;

int building[200002];
void resetPath (int n) { for (int i = 0; i <= n; i++) building[i] = i; }
int findPath (int i) { return building[i] == i ? i : building[i] = findPath (building[i]); }
bool samePath (int a, int b) { return findPath (a) == findPath (b); }
void unionPath (int a, int b) { building[findPath (a)] = findPath (b); }

int main (int argc, char const *args[]) {
    int n, m, a, b, c;
    
    while (scanf ("%d %d", &m, &n)) {
        if (m == 0 && n == 0) break;
        
        priority_queue<pair<int, pair<int, int> > > streets;
        int total=0;
        
        for (int i = 0; i < n; i++) {
            scanf ("%d %d %d", &a, &b, &c);
            streets.push (make_pair (-c, make_pair (a, b)));
            total += c;
        }
    
        int length=0, count=0;
        resetPath (m);

        while (count < m-1) {
            pair<int, pair<int, int> > street = streets.top ();
            streets.pop ();
            if (samePath (street.second.first, street.second.second)) continue;
            unionPath (street.second.first, street.second.second);
            length += -(street.first);
            count++;
        }
    
        printf ("%d\n", total - length);
    }
}