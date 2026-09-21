#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main () {
    int n, e, t, m, a, b, c;
    
    scanf ("%d", &n);
    scanf ("%d", &e);
    scanf ("%d", &t);
    scanf ("%d", &m);
    
    vector<pair<int, int> > adj[n+1];
    for (int i = 0; i < m; i++) {
        scanf ("%d %d %d", &a, &b, &c);
        adj[b].push_back (make_pair (a, c));
    }
    
    queue<int> order;
    order.push (e);
    int dist[n+1];
    bool spt[n+1];
    for (int i = 0; i <= n; i++) dist[i] = INT_MAX, spt[i] = false;
    dist[e] = 0;
    spt[e] = true;
    
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
    
    int out = 0;
    for (int i = 1; i <= n; i++) if (dist[i] <= t) out++;
    printf ("%d\n", out);
}