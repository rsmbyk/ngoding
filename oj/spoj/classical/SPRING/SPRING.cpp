#include <climits>
#include <cstdio>
#include <vector>
#include <queue>

#define pdi pair<double, int>

using namespace std;
vector<vector<pdi > >node;
int n, m, d;
double dijkstra (int from, int to) {
    
    vector<double> dist (n+2, INT_MAX);
    priority_queue<pdi, vector<pdi >, greater<pdi > > q;
    
    dist[from] = 0.0;
    q.push (make_pair (0.0, from));
    
    while (!q.empty ()) {
        pdi top = q.top ();
        q.pop ();
        double f = top.first;
        int s = top.second;
        
        if (s == to)
            return dist[to];
        
        for (int i = 0; i < node[s].size (); i++) {
            double cost = node[s][i].first;
            int next = node[s][i].second;
            
            if (cost + f < dist[next]) {
                dist[next] = cost + f;
                q.push (make_pair (dist[next], next));
            }
        }
    }
    
    return -1.0;
}

int main (int argc, char **argv) {
    
    while (scanf ("%d %d %d", &n, &m, &d) == 3) {
        node.clear ();
        node = vector<vector<pdi > > (n+2);
        while (m--) {
            int a, b, w;
            scanf ("%d %d %d", &a, &b, &w);
            double ratio = 1.0 / w;
            node[a].push_back (make_pair (ratio, b));
            node[b].push_back (make_pair (ratio, a));
        }
        
        double result = dijkstra (0, n-1);
        double f = d / result;
        f = max (f, 0.0);
        printf ("%.2f\n", f);
    }
    
    return 0;
}