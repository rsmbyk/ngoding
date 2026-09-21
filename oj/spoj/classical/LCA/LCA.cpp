#include <cstdio>
#include <vector>
#include <set>
#include <climits>
using namespace std;

int n, fo[1001];
vector<pair<int, int> > eulertour;
vector<int> tree[1001];
set<int> childs;

void buildChildData () {
    int m, node;
    childs.clear ();
    
    for (int i = 1; i <= n; i++) {
        tree[i].clear ();
        scanf ("%d", &m);
        
        for (int j = 0; j < m; j++) {
            scanf ("%d", &node);
            tree[i].push_back (node);
            childs.insert (node);
        }
    }
}

int rootnode () {
    for (int i = 1; i <= n; i++) if (childs.insert (i).second) return i;
    return 0;
}

void generateEulerTour (int node = rootnode (), int level = 0) {
    fo[node] = eulertour.size ();
    eulertour.push_back (make_pair (node, level));
    
    for (int i = 0; i < tree[node].size (); i++) {
        generateEulerTour (tree[node][i], level+1);
        eulertour.push_back (make_pair (node, level));
    }
}

int lca () {
    int v, w;
    scanf ("%d %d", &v, &w);
    
    int fov, fow;
    fov = min (fo[v], fo[w]);
    fow = max (fo[v], fo[w]);
    
    int lowest = INT_MAX, lindex = fov;
    for (int i = fov; i <= fow; i++) {
        if (eulertour[i].second < lowest) {
            lowest = eulertour[i].second;
            lindex = i;
        }
    }
    return eulertour[lindex].first;
}

int main (int argc, char const *argv[]) {
    int tc, q;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        scanf ("%d", &n);
        buildChildData ();
        generateEulerTour ();
//        for (int i = 0; i < eulertour.size (); i++) printf ("%d ", eulertour[i].first);
//        printf ("\n");
//        for (int i = 0; i < eulertour.size (); i++) printf ("%d ", eulertour[i].second);
//        printf ("\n");
//        for (int i = 0; i <= n; i++) printf ("%d ", fo[i]);
//        printf ("\n");
//        for (int i = 0; i < eulertour.size (); i++) {
//            for (int j = 0; j < eulertour.size (); j++) printf ("%d ", lookup[i][j]);
//            printf ("\n");
//        }
        scanf ("%d", &q);
        printf ("Case %d:\n", t);
        for (int i = 0; i < q; i++) printf ("%d\n", lca ());
    }
}