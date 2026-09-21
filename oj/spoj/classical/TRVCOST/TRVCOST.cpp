#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main (int argc, char const *args[]) {
    int n, s, m, a, b, c;
    scanf ("%d", &n);
    vector<pair<int, int> > adj[505];
    
    for (int i = 0; i < n; i++) {
        scanf ("%d %d %d", &a, &b, &c);
        adj[a].push_back (make_pair (b, c));
        adj[b].push_back (make_pair (a, c));
    }
    
    queue<int> order;
    int dist[505];
    bool spt[505];
    for (int i = 0; i < 505; i++) dist[i] = INT_MAX, spt[i] = false;
    
    scanf ("%d", &s);
    order.push (s);
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
    
    scanf ("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf ("%d", &a);
        if (dist[a] != INT_MAX) printf ("%d\n", dist[a]);
        else printf ("NO PATH\n");
    }
    return 0;
}