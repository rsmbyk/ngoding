#include <cstdio>
#include <set>
#include <cstring>
#include <vector>

std::vector<int> parent;
int findSet (int n) { return parent[n] == n ? n : parent[n] = findSet (parent[n]); }
int sameSet (int a, int b) { return findSet (a) == findSet (b); }
void initSet (int n) { for (int i = 0; i <= n; i++) parent.push_back (i); }
void unionSet (int a, int b) { parent[findSet (a)] = findSet (b); }

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, k, a, b;
        char r[5];
        
        scanf ("%d %d", &n, &k);
        parent.clear ();
        initSet (n);
        
        std::vector<int> pending[2];
        for (int i = 0; i < k; i++) {
            scanf ("%d %s %d", &a, r, &b);
            if (strcmp (r, "=") == 0) unionSet (a, b);
            else pending[0].push_back (a), pending[1].push_back (b);
        }
        
        bool valid = true;
        for (int i = 0; i < pending[0].size (); i++) {
            if (sameSet (pending[0][i], pending[1][i])) {
                valid = false;
                break;
            }
        }
        
        if (valid) printf ("YES\n");
        else printf ("NO\n");
    }
}