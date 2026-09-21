#include <cstdio>
#include <queue>
using namespace std;

int building[100001];
void resetPath (int n) { for (int i = 0; i <= n; i++) building[i] = i; }
int findPath (int i) { return building[i] == i ? i : building[i] = findPath (building[i]); }
bool samePath (int a, int b) { return findPath (a) == findPath (b); }
void unionPath (int a, int b) { building[findPath (a)] = findPath (b); }

int main (int argc, char const *args[]) {
    int tc, n, m, a, b, c, d;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &n, &m);
        vector<int> milkmans;
        resetPath (n);
        
        for (int i = 0; i < n; i++) {
            scanf ("%d", &d);
            if (d == 1) milkmans.push_back (i+1);
        }
        
        for (int i = 0; i < (int) milkmans.size ()-1; i++) unionPath (milkmans[i], milkmans[i+1]);
        priority_queue<pair<int, pair<int, int> > > roads;
        
        for (int i = 0; i < m; i++) {
            scanf ("%d %d %d", &a, &b, &c);
            roads.push (make_pair (-c, make_pair (a, b)));
        }
        
        long long cost=0, count=milkmans.size ()-1;
        while (count < n-1) {
            if (roads.empty ()) break;
            pair<int, pair<int, int> > road = roads.top ();
            roads.pop ();
            if (samePath (road.second.first, road.second.second)) continue;
            unionPath (road.second.first, road.second.second);
            cost += -(road.first);
            count++;
        }
        
        if (count == n-1) printf ("%lld\n", cost);
        else printf ("impossible\n");
    }
}