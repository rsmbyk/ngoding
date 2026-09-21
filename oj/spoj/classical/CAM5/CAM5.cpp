#include <cstdio>
#include <vector>
#include <set>

std::vector<int> groups;
int findSet (int n) { return groups[n] == n ? n : groups[n] = findSet (groups[n]); }
int sameSet (int a, int b) { return findSet (a) == findSet (b); }
void initSet (int n) { for (int i = 0; i <= n; i++) groups.push_back (i); }
void unionSet (int a, int b) { groups[findSet (a)] = findSet (b); }

int main (int args, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, m;
        scanf ("%d", &n);
        scanf ("%d", &m);
        
        groups.clear ();
        initSet (n);
        int a, b;
        
        for (int i = 0; i < m; i++) {
            scanf ("%d %d", &a, &b);
            unionSet (a, b);
        }
        
        std::set<int> peerGroup;
        for (int i = 0; i < n; i++) peerGroup.insert (findSet (groups[i]));
        printf ("%d\n", peerGroup.size ());
    }
}