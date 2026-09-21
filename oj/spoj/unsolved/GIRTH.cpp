#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
bool visited[1005], revisited[1005];
vector<int> adj[1005];

int isCyclic (int v, int parent) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size (); i++) {
        if (!visited[adj[v][i]]) {
            int res = isCyclic (adj[v][i], v);
            if (res != 0) return res;
        }
        else if (adj[v][i] != parent) return adj[v][i];
    }
    
    return 0;
}

int min_val[1005];
deque<int> final;

bool temp (int v, int parent, deque<int> tour, int res) {
    //printf ("visiting %d, sofar %d\n", v, tour.size ());
    while (true) {
        tour.push_back (v);
        //for (int i = 0; i < tour.size (); i++) printf ("%d ", tour[i]);
        //printf ("\n");
        min_val[v] = tour.size ();
        revisited[v] = true;
    
        for (int i = 0; i < adj[v].size (); i++) {
            int a = adj[v][i];
            if (a == parent) continue;
            if (!revisited[a]) {
                bool result = temp (a, v, tour, res);
                if (result) return true;
            }
            else {
                if (a == res && a != parent) {
                    if (final.size () == 0 || tour.size () < final.size ()) final = tour;
                }
                else if (tour.size () < min_val[a]) temp (a, v, tour, res);
            }
        }
    }
}

int main (int argc, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        int n, m, a, b;
        scanf ("%d %d", &n, &m);
        
        for (int i = 0; i <= n; i++) visited[i] = 0, adj[i].clear ();
        for (int i = 0; i < m; i++) {
            scanf ("%d %d", &a, &b);
            if (a > n || b > n) continue;
            adj[a].push_back (b);
            adj[b].push_back (a);
        }
        
        for (int i = 1; i <= n; i++) std::sort (adj[i].begin (), adj[i].end ());
        
        for (int i = 1; i <= n; i++) {
            if (visited[i]) continue;
            int res = isCyclic (i, 0);
            //printf ("res: %d\n", res);
            if (res != 0) {
                for (int j = 0; j <= n; j++) {
                    revisited[j] = false;
                    min_val[j] = 10000;
                }
                
                temp (res, 0, deque<int> (), res);
                printf ("Final: ");
                for (int j = 0; j < final.size (); j++) printf ("%d ", min_val[final[j]]);
                printf ("\n");
            }
        }
        
        printf ("Case #%d: ", t);
        if (final.size () == 0) printf ("-1\n");
        else {
            printf ("%d", final.size ());
            for (int i = 0; i < final.size (); i++) printf (" %d", final[i]);
            printf (" %d\n", final[0]);
        }
    }
}