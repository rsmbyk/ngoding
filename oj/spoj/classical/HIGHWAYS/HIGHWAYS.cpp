#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main () {
    int tc, n, m, s, e, a, b, c;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d %d %d", &n, &m, &s, &e);
        vector<pair<int, int> > adj[ n+1 ];
        
        for (int i = 0; i < m; i++) {
            scanf ("%d %d %d", &a, &b, &c);
            adj[ a ].push_back (make_pair (b, c));
            adj[ b ].push_back (make_pair (a, c));
        }
        
        queue<int> order;
        order.push (s);
        int dist[ n+1 ], now;
        bool spt[ n+1 ];
        for (int i = 0; i <= n; i++) dist[i] = INT_MAX, spt[i] = false;
        dist[s] = 0;
        spt[s] = true;
        
        while (!order.empty ()) {
            int u = order.front ();
            order.pop ();
            
            for (int i = 0; i < adj[u].size (); i++) {
                pair<int, int> next = adj[u][i];
                if (spt[ next.first ] && dist[u] != INT_MAX && (dist[u] + next.second >= dist[next.first])) continue;
                dist[next.first] = dist[u] + next.second;
                spt[next.first] = true;
                order.push (next.first);
            }
        }
        
        if (dist[e] != INT_MAX) printf ("%d\n", dist[e]);
        else printf ("NONE\n");
    }
}