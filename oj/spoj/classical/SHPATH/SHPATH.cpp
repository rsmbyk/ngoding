#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main (int argc, char const *args[]) {
    ios::sync_with_stdio (false);
    int tc, n, p, nr, c, r, s, d;
    string name, name1, name2;
    cin >> tc;
    
    while (tc--) {
        cin >> n;
        map<string, int> cities;
        vector<pair<int, int> > adj[n+1];
        
        for (int i = 1; i <= n; i++) {
            cin >> name;
            cin >> p;
            cities.insert (make_pair (name, i));
            
            for (int j = 0; j < p; j++) {
                cin >> nr >> c;
                adj[i].push_back (make_pair (nr, c));
                adj[nr].push_back (make_pair (i, c));
            }
        }
    
        cin >> r;
        while (r--) {
            priority_queue<pair<int, int> > order;
            int dist[n+1];
            bool spt[n+1];
            for (int i = 0; i <= n; i++) dist[i] = INT_MAX, spt[i] = false;
            
            cin >> name1 >> name2;
            s = cities[name1];
            d = cities[name2];
            order.push (make_pair (0, s));
            dist[s] = 0;
            spt[s] = true;
    
            while (!order.empty ()) {
                pair<int, int> u = order.top ();
                order.pop ();
                
                if (u.second == d) {
                    printf ("%d\n", dist[d]);
                    break;
                }
                
                for (int i = 0; i < adj[u.second].size (); i++) {
                    pair<int, int> next = adj[u.second][i];
                    if (spt[next.first] && dist[u.second] != INT_MAX && (dist[u.second] + next.second >= dist[next.first])) continue;
                    dist[next.first] = dist[u.second] + next.second;
                    spt[next.first] = true;
                    order.push (make_pair (-dist[next.first], next.first));
                }
            }
        }
    }
}