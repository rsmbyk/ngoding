#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

int parent[1001];
int findSet (int n) { return parent[n] == n ? n : parent[n] = findSet (parent[n]); }
int sameSet (int a, int b) { return findSet (a) == findSet (b); }
void initSet (int n) { for (int i = 0; i <= n; i++) parent[i] = i; }
void unionSet (int a, int b) { parent[findSet (a)] = findSet (b); }

int main (int argc, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        int n, m, u, v;
        scanf ("%d %d", &n, &m);
        
        int students[n+1]={};
        initSet (n);
        for (int i = 1; i <= n; i++) scanf ("%d", &students[i]);
        
        for (int i = 0; i < m; i++) {
            scanf ("%d %d", &u, &v);
            if (!sameSet (u, v)) {
                students[findSet (v)] += students[findSet (u)];
                students[findSet (u)] = 0;
                unionSet (u, v);
            }
        }
        
        std::sort (students, students+n+1);
        int i = 1;
        while (students[i] == 0 && i < n) i++;
        printf ("Case %d: %d\n", t, n-i+1);
        while (i <= n) printf ("%d ", students[i++]);
        printf ("\n");
    }
}